from   antlr4 import CommonTokenStream, InputStream
import sys

sys.path.append("../../")
from RpcTool.Parser.Grammar.RemoteCallLexer import RemoteCallLexer
from RpcTool.Parser.Grammar.RemoteCallParser import RemoteCallParser

class RpcDefinition:
    def __init__(self, text:str):
        self._text = text

    def parse(self):
        inputStream = InputStream(self._text)
        lexer = RemoteCallLexer(inputStream)
        tokenStream = CommonTokenStream(lexer)
        parser = RemoteCallParser(tokenStream)
        return parser.document()

