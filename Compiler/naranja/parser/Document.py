import typing
from naranja.parser.grammar.RemoteCallParser import RemoteCallParser
from naranja.model.Exception import ExceptionDeclaration
from naranja.model.Enumeration import EnumerationDeclaration
from naranja.model.Include import IncludeDeclaration
from naranja.model.Service import ServiceDeclaration
from naranja.model.Structure import StructureDeclaration
from naranja.model.Types import RegularType, Argument

class Document:
    def __init__(self, name: str, parseTree: RemoteCallParser.DocumentContext):
        self._name = name
        self._parseTree = parseTree
        self._includes = []
        self._services = []
        self._exceptions = []
        self._enumerations = []
        self._structures = []

    @property
    def name(self) -> str:
        return self._name
    
    @property
    def parseTree(self) -> RemoteCallParser.DocumentContext:
        return self._parseTree

    @property
    def includes(self) -> typing.List[IncludeDeclaration]:
        return self._includes
    
    @includes.setter
    def includes(self, value: typing.List[IncludeDeclaration]):
        self._includes = value
    
    @property
    def services(self) -> typing.List[ServiceDeclaration]:
        return self._services
    
    @services.setter
    def services(self, value: typing.List[ServiceDeclaration]):
        self._services = value
    
    @property
    def exceptions(self) -> typing.List[ExceptionDeclaration]:
        return self._exceptions
    
    @exceptions.setter
    def exceptions(self, value: typing.List[ExceptionDeclaration]):
        self._exceptions = value
    
    @property
    def enumerations(self) -> typing.List[EnumerationDeclaration]:
        return self._enumerations

    @enumerations.setter
    def enumerations(self, value: typing.List[EnumerationDeclaration]):
        self._enumerations = value
    
    @property
    def structures(self) -> typing.List[StructureDeclaration]:
        return self._structures
    
    @structures.setter
    def structures(self, value: typing.List[StructureDeclaration]):
        self._structures = value

    def hasTypes(self):
        return len(self.structures) > 0 or len(self.enumerations) > 0 or len(self.exceptions) > 0 
    
    def hasServices(self):
        return len(self.services) > 0
    
    def getStructureArgs(self, name: str) -> typing.List[Argument]:
        for structure in self.structures:
            return structure.args
        raise RuntimeError("Unknown type.")
    
