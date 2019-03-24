from TestCommon import RpcDefinition
from RpcTool.Model.Include import IncludeDeclaration
from RpcTool.Model.Types import Argument, RegularType
from RpcTool.Parser.Visitors.IncludeVisitor import IncludeVisitor

def test_ParseIncludes_MultipleIncludes_Parsed():
    text =  """
            include \"common.thrift\"
            include \"shared.thrift\"
            """
    tree = RpcDefinition(text).parse()

    visitor = IncludeVisitor()
    includes = visitor.visit(tree)

    assert len(includes) == 2
    assert includes[0].name == "common"
    assert includes[0].fileName == "common.thrift"
    assert includes[1].name == "shared"
    assert includes[1].fileName == "shared.thrift"