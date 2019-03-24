from RpcTool.Model.Types import RegularType, Argument
import typing

class FunctionDeclaration:
    def __init__(self, name: str):
        self._name = name
        self._returnType = RegularType("void")
        self._args = []
        self._exceptions = []

    @property
    def name(self) -> str:
        return self._name

    @property
    def returnType(self) -> RegularType:
        return self._returnType

    @returnType.setter
    def returnType(self, value: RegularType):
        self._returnType = value

    @property
    def args(self)-> typing.List[Argument]:
        return self._args

    @args.setter
    def args(self, value: typing.List[Argument]):
        self._args = value

    @property
    def exceptions(self) -> typing.List[Argument]:
        return self._exceptions

    @exceptions.setter
    def exceptions(self, value: typing.List[Argument]):
        self._exceptions = value
    
    def __eq__(self, other):
        return type(self) == type(other)\
            and self.name == other.name and self.returnType == other.returnType\
            and self.exceptions == other.exceptions and self.args == other.args

class ServiceDeclaration:
    def __init__(self, name: str):
        self._name = name
        self._functions = []
        self._callbacks = []

    @property
    def name(self) -> str:
        return self._name

    @property
    def functions(self) -> typing.List[FunctionDeclaration]:
        return self._functions
    
    @property
    def callbacks(self) -> typing.List[FunctionDeclaration]:
        return self._callbacks
    
    def __eq__(self, other):
        return type(self) == type(other) and self.name == other.name\
            and self.functions == other.functions






    