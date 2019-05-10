import typing
from naranja.model.Types import Argument

class StructureDeclaration:
    def __init__(self, name: str):
        self._name = name
        self._args = []
    
    @property
    def name(self) -> str:
        return self._name
    
    @name.setter
    def name(self, value: str):
        self._name = value

    @property
    def args(self) -> typing.List[Argument]:
        return self._args
    
    @args.setter
    def args(self, value: typing.List[Argument]):
        self._args = value
    
    def __eq__(self, other):
        return type(self) == type(other) and self.name == other.name\
            and self.args == other.args