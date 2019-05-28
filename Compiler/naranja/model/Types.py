import typing

class BaseType:
    def __init__(self, name: str):
        self._name = name

    @property
    def name(self) -> str:
        return self._name

    def isPrimitive(self):
        return self._name in ["bool", "i8", "i16", "i32", "i64", "u8", "u16", "u32", "u64", "float", "double", "string", "binary"]

class RegularType(BaseType):
    def __init__(self, name: str, namespace: str = None):
        super().__init__(name)
        self._namespace = namespace

    @property
    def namespace(self) -> str:
        return self._namespace
    
    def __eq__(self, other):
        return type(self) == type(other) and self.name == other.name and self.namespace == other.namespace

class ListType(BaseType):
    def __init__(self, valueType: BaseType):
        super().__init__(name = "list")
        self._valueType = valueType

    @property
    def valueType(self) -> BaseType:
        return self._valueType
    
    def __eq__(self, other):
        return type(self) == type(other) and self.valueType == other.valueType

class Argument:
    def __init__(self, uniqueId: int, valueType: BaseType, name: str):
        self._uniqueId = uniqueId
        self._valueType = valueType
        self._name = name

    @property
    def uniqueId(self) -> int:
        return self._uniqueId
    
    @property
    def valueType(self) -> BaseType:
        return self._valueType
    
    @property
    def name(self) -> str:
        return self._name

    def __eq__(self, other):
        return type(self) == type(other) and self.uniqueId == other.uniqueId\
            and self.name == other.name\
            and self.valueType == other.valueType
