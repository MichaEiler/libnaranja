from naranja.parser.grammar.RemoteCallVisitor import RemoteCallVisitor
from naranja.parser.grammar.RemoteCallParser import RemoteCallParser
from naranja.model.Types import RegularType, ListType, Argument

class ArgsVisitor(RemoteCallVisitor):
    def visitArgs(self, ctx:RemoteCallParser.ArgsContext):
        args = [ ctx.arg().accept(self) ]
        
        if ctx.args() != None:
            args.extend(ctx.args().accept(self))

        return args

    def visitArg(self, ctx:RemoteCallParser.ArgContext):
        def parseNumber(value:str):
            if value.startswith("0x"):
                return int(value, 16)
            return int(value)

        number = parseNumber(str(ctx.Number()))
        name = str(ctx.Identifier())
        someType = ctx.someType().accept(self)

        return Argument(number, someType, name)

    def visitSomeType(self, ctx:RemoteCallParser.SomeTypeContext):
        if ctx.listType() != None:
            innerType = ctx.listType().regularType().accept(self);
            return ListType(innerType)
        else:
            return ctx.regularType().accept(self)

    def visitRegularType(self, ctx:RemoteCallParser.RegularTypeContext):
        if ctx.Identifier(1) == None:
            return RegularType(str(ctx.Identifier(0)))
        else:
            namespace = str(ctx.Identifier(0))
            name = str(ctx.Identifier(1))
            return RegularType(name, namespace)