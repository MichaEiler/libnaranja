from naranja.parser.grammar.RemoteCallParser import RemoteCallParser
from naranja.parser.grammar.RemoteCallVisitor import RemoteCallVisitor
from naranja.model.Include import IncludeDeclaration

class IncludeVisitor(RemoteCallVisitor):
    def visitDocument(self, ctx:RemoteCallParser.DocumentContext):
        importedFiles = []
        for i in range(ctx.getChildCount()):
            child = ctx.getChild(i)
            result = child.accept(self)
            if result != None:
                importedFiles.append(result)
    
        return importedFiles

    def visitInclude(self, ctx:RemoteCallParser.IncludeContext):
        name = str(ctx.Identifier(0))
        extension = str(ctx.Identifier(1))
        return IncludeDeclaration(name, "{0}.{1}".format(name, extension))

    def visitService(self, ctx:RemoteCallParser.ServiceContext):
        return None
    
    def visitStructure(self, ctx:RemoteCallParser.StructureContext):
        return None

    def visitException(self, ctx:RemoteCallParser.ExceptionContext):
        return None
    
    def visitEnumeration(self, ctx:RemoteCallParser.EnumerationContext):
        return None

