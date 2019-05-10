from naranja.parser.grammar.RemoteCallVisitor import RemoteCallVisitor
from naranja.parser.grammar.RemoteCallParser import RemoteCallParser
from naranja.parser.Document import Document

class EnumerationTypeVisitor(RemoteCallVisitor):
    def __init__(self, knownExceptions, documentName):
        self._knownExceptions = knownExceptions
        self._documentName = documentName

    def visitRegularType(self, ctx:RemoteCallParser.RegularTypeContext):
        first = ctx.Identifier(0)
        second = ctx.Identifier(1)
        exceptionName = str(first) if second == None else "{0}.{1}".format(str(first), str(second))

        if not exceptionName in self._knownExceptions:
            raise RuntimeError("The exception {0} is not known within the document {1}.".format(exceptionName, self._documentName))

class VariableTypeVisitor(RemoteCallVisitor):
    def __init__(self, knownTypes, documentName):
        self._knownTypes = knownTypes
        self._documentName = documentName
    
    def _isBaseType(self, name):
        types = ['i8', 'i16', 'i32', 'i64', 'u8', 'u16', 'u32', 'u64', 'double', 'float', 'binary', 'string', 'bool']
        return name in types
    
    def visitRegularType(self, ctx:RemoteCallParser.RegularTypeContext):
        first = ctx.Identifier(0)
        second = ctx.Identifier(1)
        typeName = str(first) if second == None else "{0}.{1}".format(str(first), str(second))

        if not self._isBaseType(typeName) and not typeName in self._knownTypes:
            raise RuntimeError("The type {0} is not known within the document {1}.".format(typeName, self._documentName))


class ValidationVisitor(RemoteCallVisitor):
    def __init__(self, documents, documentName):
        self._documentName = documentName
        self._documents = documents

        def findDocument(documents, name):
            for document in documents:
                if document.name == name:
                    return document
            
            raise RuntimeError("The document {0} does not exist in given list.".format(documentName))


        thisDocument = findDocument(documents, documentName)
        self._knownExceptions = [ exception.name for exception in thisDocument.exceptions ]
        self._knownTypes = [ structure.name for structure in thisDocument.structures ]
        self._knownTypes.extend([ e.name for e in thisDocument.enumerations ]) # structures AND enums

        for includedDocumentName in [i.name for i in thisDocument.includes]:
            includedDocument = findDocument(documents, includedDocumentName)
            
            self._knownExceptions.extend([includedDocumentName + "." + e.name for e in includedDocument.exceptions])
            self._knownTypes.extend([includedDocumentName + "." + e.name for e in includedDocument.enumerations])
            self._knownTypes.extend([includedDocumentName + "." + s.name for s in includedDocument.structures])


    def visitFunction(self, ctx:RemoteCallParser.FunctionContext):
        if ctx.Throws() != None:
            exceptionsChild = ctx.args(1) if ctx.args(1) != None else ctx.args(0)
            visitor = EnumerationTypeVisitor(self._knownExceptions, self._documentName)
            exceptionsChild.accept(visitor)
        
        argsChild = None
        if (ctx.args(0) != None and ctx.Throws() == None) or ctx.args(1) != None:
            argsChild = ctx.args(0)
        
        visitor = VariableTypeVisitor(self._knownTypes, self._documentName)
        if argsChild != None:
            argsChild.accept(visitor)
        
        def hasReturnValue(child):
            if isinstance(child.regularType(), RemoteCallParser.RegularTypeContext):
                if str(child.regularType().Identifier(0)) == "void":
                    return False
            return True

        if hasReturnValue(ctx.someType()):
            ctx.someType().accept(visitor)
        
    
    def visitStructure(self, ctx:RemoteCallParser.StructureContext):
        visitor = VariableTypeVisitor(self._knownTypes, self._documentName)

        for i in range(ctx.getChildCount()):
            child = ctx.getChild(i)
            child.accept(visitor)
    
    def visitException(self, ctx:RemoteCallParser.ExceptionContext):
        visitor = VariableTypeVisitor(self._knownTypes, self._documentName)

        for i in range(ctx.getChildCount()):
            child = ctx.getChild(i)
            child.accept(visitor)
