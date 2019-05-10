import typing
from naranja.model.Types import Argument

class EnumerationDeclaration:
    def __init__(self, name: str):
        self._name = name
        self._values = [ ]

    @property
    def name(self) -> str:
        return self._name
    
    @name.setter
    def name(self, value: str):
        self._name = value

    @property
    def values(self):
        return self._values
    
    @values.setter
    def values(self, value):
        self._values = value
    
    def __eq__(self, other):
        return type(self) == type(other)\
            and self.name == other.name\
            and self.values == other.values
