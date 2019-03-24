class BaseType:
    pass

class RegularType(BaseType):
    def __init__(self, name: str, namespace: str = None):
        self._name = name
        self._namespace = namespace

    @property
    def name(self) -> str:
        return self._name

    @property
    def namespace(self) -> str:
        return self._namespace
    
    def __eq__(self, other):
        return type(self) == type(other) and self.name == other.name and self.namespace == other.namespace

class ListType(BaseType):
    def __init__(self, valueType: RegularType):
        self._valueType = valueType

    @property
    def valueType(self) -> RegularType:
        return self._valueType
    
    def __eq__(self, other):
        return type(self) == type(other) and self.valueType == other.valueType

class MapType(BaseType):
    def __init__(self, key: RegularType, valueType: RegularType):
        self._key = key
        self._valueType = valueType

    @property
    def key(self) -> RegularType:
        return self._key

    @property
    def valueType(self) -> RegularType:
        return self._valueType
    
    def __eq__(self, other):
        return type(self) == type(other) and self.key == other.key and self.valueType == other.valueType

class SetType(BaseType):
    def __init__(self, valueType: RegularType):
        self._valueType = valueType

    @property
    def valueType(self) -> RegularType:
        return self._valueType
    
    def __eq__(self, other):
        return type(self) == type(other) and self.valueType == other.valueType

class Argument:
    def __init__(self, uniqueId: int, valueType: RegularType, name: str):
        self._uniqueId = uniqueId
        self._valueType = valueType
        self._name = name

    @property
    def uniqueId(self) -> int:
        return self._uniqueId
    
    @property
    def valueType(self) -> RegularType:
        return self._valueType
    
    @property
    def name(self) -> str:
        return self._name

    def __eq__(self, other):
        return type(self) == type(other) and self.uniqueId == other.uniqueId\
            and self.name == other.name\
            and self.valueType == other.valueType
