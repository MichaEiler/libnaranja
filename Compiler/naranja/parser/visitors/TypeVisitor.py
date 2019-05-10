from naranja.parser.grammar.RemoteCallParser  import RemoteCallParser
from naranja.parser.grammar.RemoteCallVisitor import RemoteCallVisitor
from naranja.parser.visitors.ArgsVisitor      import ArgsVisitor
from naranja.model.Structure           import StructureDeclaration
from naranja.model.Exception           import ExceptionDeclaration
from naranja.model.Enumeration         import EnumerationDeclaration

class StructureVisitor(RemoteCallVisitor):
    def visitDocument(self, ctx:RemoteCallParser.DocumentContext):
        structures = []

        for i in range(ctx.getChildCount()):
            child = ctx.getChild(i)
            structure = child.accept(self)
            if structure != None:
                structures.append(structure)

        return structures
    
    def visitStatement(self, ctx:RemoteCallParser.StatementContext):
        if isinstance(ctx.getChild(0), RemoteCallParser.StructureContext):
            return ctx.getChild(0).accept(self)
        return None

    def visitStructure(self, ctx:RemoteCallParser.StructureContext):
        name = str(ctx.Identifier())
        structure = StructureDeclaration(name)
        
        memberIds = set()

        visitor = ArgsVisitor()
        i = 0
        while ctx.declaration(i) != None:
            argNode = ctx.declaration(i).arg()
            arg = visitor.visitArg(argNode)
            structure.args.append(arg)
            memberIds.add(arg.uniqueId)
            i += 1
        
        if len(memberIds) != len(structure.args):
            raise RuntimeError("The members of structure {0} have ambiguous ids.".format(name))

        return structure

class ExceptionVisitor(RemoteCallVisitor):
    def visitDocument(self, ctx:RemoteCallParser.DocumentContext):
        exceptions = []

        for i in range(ctx.getChildCount()):
            child = ctx.getChild(i)
            exception = child.accept(self)
            if exception != None:
                exceptions.append(exception)

        return exceptions

    def visitStatement(self, ctx:RemoteCallParser.StatementContext):
        if isinstance(ctx.getChild(0), RemoteCallParser.ExceptionContext):
            return ctx.getChild(0).accept(self)
        return None

    def visitException(self, ctx:RemoteCallParser.ExceptionContext):
        name = str(ctx.Identifier())
        exception = ExceptionDeclaration(name)
        
        memberIds = set()

        argsVisitor = ArgsVisitor()
        i = 0
        while ctx.declaration(i) != None:
            argNode = ctx.declaration(i).arg()
            arg = argNode.accept(argsVisitor)
            exception.args.append(arg)
            memberIds.add(arg.uniqueId)
            i += 1
        
        if len(memberIds) != len(exception.args):
            raise RuntimeError("The members of exception {0} have ambiguous ids.".format(name))

        return exception

class EnumerationVisitor(RemoteCallVisitor):
    def visitDocument(self, ctx:RemoteCallParser.DocumentContext):
        enumerations = []

        for i in range(ctx.getChildCount()):
            child = ctx.getChild(i)
            enumeration = child.accept(self)
            if enumeration != None:
                enumerations.append(enumeration)
            
        return enumerations
    
    def visitStatement(self, ctx:RemoteCallParser.StatementContext):
        if isinstance(ctx.getChild(0), RemoteCallParser.EnumerationContext):
            return ctx.getChild(0).accept(self)

    def visitEnumeration(self, ctx:RemoteCallParser.EnumerationContext):
        name = str(ctx.Identifier())
        enumeration = EnumerationDeclaration(name)

        values = ctx.enumerationValues().accept(self)

        result = []
        previousIdentifier = -1
        for (name, value)  in values:
            previousIdentifier += 1
            if value == None:
                value = previousIdentifier
            else:
                previousIdentifier = value
            result.append((name, value))

        enumeration.values = result
        return enumeration

    def visitEnumerationValues(self, ctx:RemoteCallParser.EnumerationValuesContext):
        def convertNumber(value):
            if value == None:
                return None
            value = str(value)
            if value.startswith("0x"):
                return int(value, 16)
            return int(value)

        name = str(ctx.Identifier())
        number = convertNumber(ctx.Number())
        values = [ (name, number) ]

        if ctx.enumerationValues() != None:
            values.extend(ctx.enumerationValues().accept(self))

        return values
