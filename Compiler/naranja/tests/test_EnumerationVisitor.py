from TestCommon import RpcDefinition
from naranja.model.Enumeration import EnumerationDeclaration
from naranja.model.Types import Argument, RegularType
from naranja.parser.visitors.TypeVisitor import EnumerationVisitor

def test_ParseEnumeration_NoEnumeration_EmptyResult():
    tree = RpcDefinition("struct A { 1:i32 value; }").parse()

    visitor = EnumerationVisitor()
    enums = visitor.visit(tree)

    assert len(enums) == 0

def test_ParseEnumeration_SingleMemberNoValue_Parsed():
    tree = RpcDefinition("enum A { a }").parse()

    visitor = EnumerationVisitor()
    enums = visitor.visit(tree)

    assert len(enums) == 1
    assert enums[0].name == "A"
    assert len(enums[0].values) == 1
    name, value =  enums[0].values[0]
    assert name == "a"
    assert value == 0

def test_ParseEnumeration_MultipleMembersDifferentValues_Parsed():
    text =  """
            enum A
            {
                a,
                b = 3,
                c,
                d = 0xff,
                e,
                f
            }
            """
    tree = RpcDefinition(text).parse()

    visitor = EnumerationVisitor()
    enums = visitor.visit(tree)

    expectedNumberOfValues = 6
    expectedValues = [('a', 0), ('b', 3), ('c', 4), ('d', 255), ('e', 256), ('f', 257)]

    assert len(enums) == 1
    assert len(enums[0].values) == expectedNumberOfValues
    for i in range(expectedNumberOfValues):
        assert expectedValues[i] == enums[0].values[i]

def test_ParseEnumerations_TwoEnumerations_BothParsed():
    text =  """
            enum A { a = 0 }
            enum B { b = 1 }
            """

    tree = RpcDefinition(text).parse()
    visitor = EnumerationVisitor()
    enums = visitor.visit(tree)
    
    assert len(enums) == 2


