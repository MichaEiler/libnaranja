class IncludeDeclaration:
    def __init__(self, name: str, fileName: str):
        self._name = name
        self._fileName = fileName
    
    @property
    def name(self) -> str:
        return self._name

    @property
    def fileName(self) -> str:
        return self._fileName

    def __eq__(self, other):
        return type(self) == type(other)\
            and self.name == other.name and self.fileName == other.fileName
