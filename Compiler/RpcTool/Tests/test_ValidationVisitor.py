from TestCommon import RpcDefinition

from RpcTool.Model.Include import IncludeDeclaration
from RpcTool.Parser.RpcDocument import RpcDocument
from RpcTool.Parser.Visitors.ValidationVisitor import ValidationVisitor
from RpcTool.Parser.Visitors.ServiceVisitor import ServiceVisitor
from RpcTool.Parser.Visitors.TypeVisitor import StructureVisitor, EnumerationVisitor, ExceptionVisitor
import pytest

def test_ValidationVisitor_UnknownTypeInStructure_RaisesRuntimeError():
    def parseStructure(text:str):
        tree = RpcDefinition(text).parse()
        document = RpcDocument("test", tree)
        visitor = StructureVisitor()
        document.structures = visitor.visit(tree)
        return document

    document = parseStructure("struct A { 1:i128 a; }")
    with pytest.raises(RuntimeError):
        visitor = ValidationVisitor([document], document.name)
        visitor.visit(document.parseTree)

    document = parseStructure("struct A { 1:B b; }")
    with pytest.raises(RuntimeError):
        visitor = ValidationVisitor([document], document.name)
        visitor.visit(document.parseTree)

def test_ValidationVisitor_ImportedTypeInStructure_NoErrorThrown():
    treeA = RpcDefinition("struct A { 1:i32 a; }").parse()
    treeB = RpcDefinition("struct B { 1:Types.A a; }").parse()

    documentA = RpcDocument("Types", treeA)
    documentB = RpcDocument("test", treeB)
    documentB.includes = [ IncludeDeclaration("Types", "Types.rpc") ]
    
    visitor = StructureVisitor()
    documentA.structures = visitor.visit(treeA)
    documentB.structures = visitor.visit(treeB)

    visitor = ValidationVisitor([documentA, documentB], documentB.name)
    visitor.visit(documentB.parseTree)

def test_ValidationVisitor_ImportedEnumInStructure_NoErrorRaised():
    treeA = RpcDefinition("enum A { a = 0, b = 1 }").parse()
    treeB = RpcDefinition("struct B { 1:Types.A a; } ").parse()

    documentA = RpcDocument("Types", treeA)
    documentB = RpcDocument("test", treeB)
    documentB.includes = [ IncludeDeclaration("Types", "Types.rpc") ]

    visitor = EnumerationVisitor()
    documentA.enumerations = visitor.visit(treeA)
    visitor = StructureVisitor()
    documentB.structures = visitor.visit(treeB)

    visitor = ValidationVisitor([documentA, documentB], documentB.name)
    visitor.visit(documentB.parseTree)


def test_ValidationVisitor_FunctionOnlyThrowsExceptions_NoErrorRaised():
    treeA = RpcDefinition("exception RuntimeException { 1:string description; }").parse()
    treeB = RpcDefinition("exception ConfigurationException { 1:string description; }").parse()
    treeC = RpcDefinition(  """
                            exception ParameterException { 1:string description; }
                            service MainService {
                                void Foo() throws (1:Types.RuntimeException ex, 2:Configuration.ConfigurationException ex, 3:ParameterException ex)
                                void Bar(1:i32 foobar) throws(1:Types.RuntimeException ex)
                            }
                            """).parse()
    
    documentA = RpcDocument("Types", treeA)
    documentB = RpcDocument("Configuration", treeB)
    documentC = RpcDocument("Main", treeC)

    visitor = ExceptionVisitor()
    documentA.exceptions = visitor.visit(treeA)
    documentB.exceptions = visitor.visit(treeB)
    documentC.exceptions = visitor.visit(treeC)
    visitor = ServiceVisitor()
    documentC.services = visitor.visit(treeC)
    documentC.includes = [ IncludeDeclaration("Types", "Types.rpc"), IncludeDeclaration("Configuration", "Configuration.rpc") ]

    visitor = ValidationVisitor([documentA, documentB, documentC], documentC.name)
    visitor.visit(documentC.parseTree)

def test_ValidationVisitor_FunctionThrowsNonException_ErrorRaised():
    tree = RpcDefinition("service MainService { void Foo() throws (1:i64 ex) }").parse()
    document = RpcDocument("test", tree)
    
    with pytest.raises(RuntimeError):
        visitor = ValidationVisitor([document], "test")
        visitor.visit(document.parseTree)

def test_ValidationVisitor_DifferentFunctionArgTypes_NoErrorRaised():
    tree = RpcDefinition("""
                         enum Event { foo = 0, bla = 1 }
                         struct Data { 1:Event value; }
                         service MainService {
                             void Foo(1:i64 a, 2:Event b, 3:Data c);
                         }
                         """).parse()
    
    document = RpcDocument("test", tree)

    visitor = EnumerationVisitor()
    document.enumerations = visitor.visit(document.parseTree)
    visitor = StructureVisitor()
    document.structures = visitor.visit(document.parseTree)
    visitor = ServiceVisitor()
    document.services = visitor.visit(document.parseTree)

    visitor = ValidationVisitor([document], document.name)
    visitor.visit(document.parseTree)

def test_ValidationVisitor_DifferentReturnTypes_CorrectlyHandled():

    def checkReturnTypes(functionAsText:str):
        tree = RpcDefinition("service test { "+ functionAsText + " }").parse()
        document = RpcDocument("test", tree)
        visitor = ServiceVisitor()
        document.services = visitor.visit(document.parseTree)

        visitor = ValidationVisitor([document], document.name)
        visitor.visit(document.parseTree)

    checkReturnTypes("void Foo()")
    checkReturnTypes("i64 Bar()")

    with pytest.raises(RuntimeError):
        checkReturnTypes("A Foo()")


