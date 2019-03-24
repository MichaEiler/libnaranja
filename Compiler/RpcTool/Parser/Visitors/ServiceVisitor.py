from RpcTool.Parser.Grammar.RemoteCallVisitor import RemoteCallVisitor
from RpcTool.Parser.Grammar.RemoteCallParser import RemoteCallParser
from RpcTool.Model.Service import ServiceDeclaration, FunctionDeclaration
from RpcTool.Model.Types import RegularType, ListType, MapType, SetType, Argument
from RpcTool.Parser.Visitors.ArgsVisitor import ArgsVisitor

class ServiceVisitor(RemoteCallVisitor):
    def visitDocument(self, ctx:RemoteCallParser.DocumentContext):
        services = []
        for i in range(ctx.getChildCount()):
            child = ctx.getChild(i)
            result = child.accept(self)
            if result != None:
                services.append(result)
        return services

    def visitService(self, ctx:RemoteCallParser.ServiceContext):
        name = str(ctx.Identifier())
        service = ServiceDeclaration(name)

        i = 0
        while ctx.function(i) != None:
            function = ctx.function(i)
            parsedFunction = function.accept(self)
            if function.Callback() != None:
                service.callbacks.append(parsedFunction)
            else:
                service.functions.append(parsedFunction)
            i += 1
    
        return service

    def visitFunction(self, ctx:RemoteCallParser.FunctionContext):
        function = FunctionDeclaration(str(ctx.Identifier()))
        
        argsVisitor = ArgsVisitor()
        function.returnType = ctx.someType().accept(argsVisitor)

        def areIdsUnique(args):
            idSet = set()
            for arg in args:
                idSet.add(arg.uniqueId)
            return len(idSet) == len(args)

        argumentsChild = ctx.args(0) if ctx.args(0) != None and (ctx.Throws() == None or ctx.args(1) != None) else None 
        if argumentsChild != None:
            function.args = argumentsChild.accept(self)
            if not areIdsUnique(function.args):
                raise RuntimeError("The argument ids of function {0} are not unique.".format(function.name))

        exceptionsChild = ctx.args(0) if ctx.args(1) == None and ctx.Throws() != None else ctx.args(1) if ctx.args(1) != None else None
        if exceptionsChild != None:
            function.exceptions = exceptionsChild.accept(self)
            if not areIdsUnique(function.exceptions):
                raise RuntimeError("The exception ids of function {0} are not unique.".format(function.name))

        return function

    def visitArgs(self, ctx:RemoteCallParser.ArgsContext):
        argsVisitor = ArgsVisitor()
        return ctx.accept(argsVisitor)


