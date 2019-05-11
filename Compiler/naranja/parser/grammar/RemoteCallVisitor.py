# Generated from RemoteCall.g4 by ANTLR 4.7.1
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .RemoteCallParser import RemoteCallParser
else:
    from RemoteCallParser import RemoteCallParser

# This class defines a complete generic visitor for a parse tree produced by RemoteCallParser.

class RemoteCallVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by RemoteCallParser#document.
    def visitDocument(self, ctx:RemoteCallParser.DocumentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#statement.
    def visitStatement(self, ctx:RemoteCallParser.StatementContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#include.
    def visitInclude(self, ctx:RemoteCallParser.IncludeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#structure.
    def visitStructure(self, ctx:RemoteCallParser.StructureContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#exception.
    def visitException(self, ctx:RemoteCallParser.ExceptionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#enumeration.
    def visitEnumeration(self, ctx:RemoteCallParser.EnumerationContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#enumerationValues.
    def visitEnumerationValues(self, ctx:RemoteCallParser.EnumerationValuesContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#service.
    def visitService(self, ctx:RemoteCallParser.ServiceContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#function.
    def visitFunction(self, ctx:RemoteCallParser.FunctionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#declaration.
    def visitDeclaration(self, ctx:RemoteCallParser.DeclarationContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#args.
    def visitArgs(self, ctx:RemoteCallParser.ArgsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#arg.
    def visitArg(self, ctx:RemoteCallParser.ArgContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#someType.
    def visitSomeType(self, ctx:RemoteCallParser.SomeTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#listType.
    def visitListType(self, ctx:RemoteCallParser.ListTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by RemoteCallParser#regularType.
    def visitRegularType(self, ctx:RemoteCallParser.RegularTypeContext):
        return self.visitChildren(ctx)



del RemoteCallParser