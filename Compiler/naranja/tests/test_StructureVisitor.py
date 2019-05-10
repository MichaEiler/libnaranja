from TestCommon import RpcDefinition
from naranja.model.Structure import StructureDeclaration
from naranja.model.Types import Argument, RegularType
from naranja.parser.visitors.TypeVisitor import StructureVisitor
import pytest

def test_ParseStructure_NoStructure_EmptyResult():
    tree = RpcDefinition("enum A { 1:i64 value; }").parse()

    visitor = StructureVisitor()
    structures = visitor.visit(tree)

    assert len(structures) == 0

def test_ParseStructure_SingleMemberStructure_Parsed():
    tree = RpcDefinition("struct A { 1:i64 B; }").parse()

    visitor = StructureVisitor()
    structures = visitor.visit(tree)

    assert len(structures) == 1
    assert structures[0].name == "A"

    assert len(structures[0].args) == 1
    arg = structures[0].args[0]
    assert arg.name == "B"
    assert arg.uniqueId == 1
    assert arg.valueType.name == "i64"

def test_ParseStructure_MultipleMemberStructure_Parsed():
    text = "struct A { 1:i32 B; 2:binary C; }"
    tree = RpcDefinition(text).parse()

    visitor = StructureVisitor()
    structures = visitor.visit(tree)

    assert len(structures) == 1
    assert structures[0].name == "A"

    assert len(structures[0].args) == 2
    arg1 = structures[0].args[0]
    arg2 = structures[0].args[1]

    assert arg1.name == "B"
    assert arg1.uniqueId == 1
    assert arg1.valueType.name == "i32"

    assert arg2.name == "C"
    assert arg2.uniqueId == 2
    assert arg2.valueType.name == "binary"

def test_ParseStructure_StructWithoutMember_EmptyResult():
    tree = RpcDefinition(" struct A { } ").parse()

    visitor = StructureVisitor()
    structures = visitor.visit(tree)

    assert len(structures) == 0

def test_ParseStructure_TwoStructures_BothParsed():
    text = " struct A { 1:i16 B; } struct B { 1: i32 C; } "
    tree = RpcDefinition(text).parse()

    visitor = StructureVisitor()
    structures = visitor.visit(tree)

    assert len(structures) == 2

def test_ParseStructure_MembersWithAmbiguousIds_RaisesRuntimeError():
    text = "struct A { 1:i32 a; 1:i64 b; }"
    tree = RpcDefinition(text).parse()

    visitor = StructureVisitor()
    
    with pytest.raises(RuntimeError):
        visitor.visit(tree)



