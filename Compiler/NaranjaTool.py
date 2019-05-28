import argparse
import os
import sys

sys.path.append(os.path.dirname(os.path.realpath(__file__)))

from naranja.parser.Document import Document
from naranja.parser.grammar.RemoteCallParser import RemoteCallParser
from naranja.parser.grammar.RemoteCallLexer import RemoteCallLexer
from naranja.parser.visitors.IncludeVisitor import IncludeVisitor
from naranja.parser.visitors.ServiceVisitor import ServiceVisitor
from naranja.parser.visitors.TypeVisitor import ExceptionVisitor, EnumerationVisitor, StructureVisitor
from naranja.parser.visitors.ValidationVisitor import ValidationVisitor
from naranja.codegen.CppGenerator import CppGenerator
from antlr4 import CommonTokenStream, InputStream

def ParseFile(file):
    with open(file, 'r') as file:
        text = file.read()
        stream = InputStream(text)
        lexer = RemoteCallLexer(stream)
        tokenStream = CommonTokenStream(lexer)
        parser = RemoteCallParser(tokenStream)
        return parser.document()

def LoadRpcFiles(inputDirectory):
    documents = []

    for file in os.listdir(inputDirectory):
        if not file.endswith('.rpc'):
            continue

        name = file.split('.')[0]
        print("Detected file {0}.rpc".format(name))
        tree = ParseFile("{0}/{1}.rpc".format(inputDirectory, name))
        documents.append(Document(name, tree))

    return documents

def CreateModels(documents):
    for document in documents:
        visitor = IncludeVisitor()
        document.includes = visitor.visit(document.parseTree)

        visitor = ExceptionVisitor()
        document.exceptions = visitor.visit(document.parseTree)

        visitor = EnumerationVisitor()
        document.enumerations = visitor.visit(document.parseTree)

        visitor = StructureVisitor()
        document.structures = visitor.visit(document.parseTree)

        visitor = ServiceVisitor()
        document.services = visitor.visit(document.parseTree)

    for document in documents:
        visitor = ValidationVisitor(documents, document.name)
        visitor.visit(document.parseTree)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate RPC Code.')
    parser.add_argument('-i', '--input-directory', required=True, help='The directory containing *.rpc files.')
    parser.add_argument('-o', '--output-directory', required=True, help='The directory where the genereated files should be stored.')
    parser.add_argument('-l', '--language', required=True, help='The language for which to generate the code.', choices=['cpp17'])
    args = parser.parse_args()

    documents = LoadRpcFiles(args.input_directory)
    CreateModels(documents)
    generator = CppGenerator(documents, args.output_directory)
    generator.render()
