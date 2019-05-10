from   antlr4 import CommonTokenStream, InputStream
import sys

sys.path.append("../../")
from naranja.parser.grammar.RemoteCallLexer import RemoteCallLexer
from naranja.parser.grammar.RemoteCallParser import RemoteCallParser

class RpcDefinition:
    def __init__(self, text:str):
        self._text = text

    def parse(self):
        inputStream = InputStream(self._text)
        lexer = RemoteCallLexer(inputStream)
        tokenStream = CommonTokenStream(lexer)
        parser = RemoteCallParser(tokenStream)
        return parser.document()

