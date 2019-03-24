import TestCommon

from RpcTool.Model.Types import Argument, RegularType
from RpcTool.Model.Structure import StructureDeclaration

def test_ArgumentEquality_Equal_ResultTrue():
    arg1 = Argument(1, RegularType('double'), 'a')
    arg2 = Argument(1, RegularType('double'), 'a')

    assert arg1 == arg2

def test_ArgumentEquality_NotEqual_ResultFalse():
    arg1 = Argument(1, RegularType('double'), 'a')
    arg2 = Argument(1, RegularType('i64'), 'a')

    assert arg1 != arg2

def test_StructureEquality_Equal_ResultTrue():
    arg1 = Argument(1, RegularType('double'), 'a')
    arg2 = Argument(2, RegularType('i64'), 'a')

    struct1 = StructureDeclaration('A')
    struct2 = StructureDeclaration('A')
    struct1.args = [ arg1, arg2 ]
    struct2.args = [ arg1, arg2 ]

    assert struct1 == struct2

def test_StructureEquality_NotEqual_ResultFalse():
    arg1 = Argument(1, RegularType('double'), 'a')
    arg2 = Argument(2, RegularType('i64'), 'a')

    struct1 = StructureDeclaration('A')
    struct2 = StructureDeclaration('A')
    struct1.args = [ arg1, arg2 ]
    struct2.args = [ arg1 ]

    assert struct1 != struct2

