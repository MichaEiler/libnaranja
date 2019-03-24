from TestCommon import RpcDefinition
from RpcTool.Model.Exception import ExceptionDeclaration
from RpcTool.Model.Types import Argument, RegularType
from RpcTool.Parser.Visitors.TypeVisitor import ExceptionVisitor
import pytest

def test_ParseExceptions_NoException_Parsed():
    tree = RpcDefinition("enum A { a = 0 }").parse()

    visitor = ExceptionVisitor()
    exceptions = visitor.visit(tree)

    assert len(exceptions) == 0

def test_ParseExceptions_SingleException_Parsed():
    text =  """
            exception A {
                1:i32 a;
                2:i64 b;
                4:binary c;
            }
            """
    tree = RpcDefinition(text).parse()

    visitor = ExceptionVisitor()
    exceptions = visitor.visit(tree)

    assert len(exceptions) == 1
    expectedNumberOfValues = 3
    expectedValues = [(1, 'i32', 'a'), (2, 'i64', 'b'), (4, 'binary', 'c')]

    assert len(exceptions[0].args) == expectedNumberOfValues
    for i in range(expectedNumberOfValues):
        arg = exceptions[0].args[i]
        actualValue = (arg.uniqueId, arg.valueType.name, arg.name)

        assert expectedValues[i] == actualValue

def test_ParseExceptions_TwoExceptions_BothParsed():
    text =  """
            exception A { 1:i32 a; }
            exception B { 1:i64 b; }
            """
    tree = RpcDefinition(text).parse()

    visitor = ExceptionVisitor()
    exceptions = visitor.visit(tree)

    assert len(exceptions) == 2

def test_ParseExceptions_MembersWithAmbiguousIds_RaisesRuntimeError():
    text =  "exception A { 42:i32 a; 42:i64 b; }"
    tree = RpcDefinition(text).parse()

    visitor = ExceptionVisitor()
    
    with pytest.raises(RuntimeError):
        visitor.visit(tree)





