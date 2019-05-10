from TestCommon import RpcDefinition
from naranja.model.Types import Argument, RegularType
from naranja.parser.visitors.ServiceVisitor import ServiceVisitor
from naranja.parser.visitors.IncludeVisitor import IncludeVisitor
from naranja.parser.visitors.TypeVisitor import EnumerationVisitor, ExceptionVisitor, StructureVisitor
import pytest

def test_ParseServices_SingleService_Parsed():
    text =  """
            service A {
                void a(1:i64 b),
                binary b(3:i16 c);
            }
            """
    tree = RpcDefinition(text).parse()

    visitor = ServiceVisitor()
    services = visitor.visit(tree)

    assert len(services) == 1
    assert services[0].name == "A"
    assert len(services[0].functions) == 2

def test_ParseServices_ComplexFunctionDefinition_Parsed():
    text =  """
            service A {
                void Foo(1:i64 a, 2:i32 b, 4:i16 c) throws (1:ConfigurationException a, 2:RuntimeError b);
            }
            """
    tree = RpcDefinition(text).parse()

    visitor = ServiceVisitor()
    services = visitor.visit(tree)

    assert len(services) == 1
    assert len(services[0].functions) == 1
    
    function = services[0].functions[0]
    assert function.name == "Foo"

    expectedNumberOfArguments = 3
    expectedArguments = [(1, 'i64', 'a'), (2, 'i32', 'b'), (4, 'i16', 'c')]
    expectedNumberOfExceptions = 2
    expectedExceptions = [(1, 'ConfigurationException', 'a'), (2, 'RuntimeError', 'b')]

    for i in range(expectedNumberOfArguments):
        argument = function.args[i]
        argument = (argument.uniqueId, argument.valueType.name, argument.name)
        assert expectedArguments[i] == argument

    for i in range(expectedNumberOfExceptions):
        exception = function.exceptions[i]
        exception = (exception.uniqueId, exception.valueType.name, exception.name)
        assert expectedExceptions[i] == exception

def test_ParseServices_FunctionWithoutArgumentsButExceptions_Parsed():
    text =  """
            exception ArgumentError { 1:i32 description; }
            exception ConfigurationError { 1:i32 description; }

            service Foo
            {
                void Bar() throws (1:ArgumentError error, 2:ConfigurationError error);
            }
            """
    tree = RpcDefinition(text).parse()

    visitor = ServiceVisitor()
    services = visitor.visit(tree)

    assert len(services) == 1
    assert len(services[0].functions) == 1
    assert len(services[0].functions[0].args) == 0
    assert len(services[0].functions[0].exceptions) == 2

def test_ParseServices_FullSample_Parsed():
    text =  """
            
            include \"Types.thrift\"
            
            exception InvalidHandle
            {
                1:i32 c;
                2:binary d;
            }

            struct Parameters
            {
                1:i64 a;
                2:i16 b;
            }

            enum OperationMode
            {
                Sync = 4,
                Async,
                Both = 0x87
            }

            service Database
            {
                void Run(0xf:i32 a, 2:i64 b);
                void Stop(3:i64 c);
            }
            """
    tree = RpcDefinition(text).parse()

    visitor = IncludeVisitor()
    includes = visitor.visit(tree)
    assert len(includes) == 1

    visitor = ExceptionVisitor()
    exceptions = visitor.visit(tree)
    assert len(exceptions) == 1

    visitor = StructureVisitor()
    structures = visitor.visit(tree)
    assert len(structures) == 1

    visitor = EnumerationVisitor()
    enums = visitor.visit(tree)
    assert len(enums) == 1

    visitor = ServiceVisitor()
    services = visitor.visit(tree)
    assert len(services) == 1

def test_ParseServices_FunctionWithAmbiguousArgumentIds_RaisesRuntimeError():
    text =  """
            service Foo
            {
                void Bar(1:i16 foo, 1:i32 bar);
            }
            """
    
    definition = RpcDefinition(text)
    tree = definition.parse()

    visitor = ServiceVisitor()

    with pytest.raises(RuntimeError):
        visitor.visit(tree)

def test_ParseServices_FunctionWithAmbiguousExceptionIds_RaisesRuntimeError():
    text =  """
            exception ArgumentError { 1:i32 description; }
            exception ConfigurationError { 1:i32 description; }

            service Foo
            {
                void Bar() throws (1:ArgumentError error, 1:ConfigurationError error);
            }
            """
    
    definition = RpcDefinition(text)
    tree = definition.parse()

    visitor = ServiceVisitor()

    with pytest.raises(RuntimeError):
        visitor.visit(tree)

def test_ParseServices_FunctionMarkesAsCallback_SuccessfullyParsed():
    text =  """
            service Foo
            {
                [[callback]] void Bar();
            }
            """

    definition = RpcDefinition(text)
    tree = definition.parse()
    
    visitor = ServiceVisitor()

    services = visitor.visit(tree)
    assert len(services) == 1
    assert len(services[0].callbacks) == 1
    assert services[0].callbacks[0].name == "Bar"

