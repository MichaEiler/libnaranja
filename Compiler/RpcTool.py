import argparse
import os
import sys

sys.path.append(os.path.dirname(os.path.realpath(__file__)))

from RpcTool.Parser.RpcDocument import RpcDocument
from RpcTool.Parser.Grammar.RemoteCallParser import RemoteCallParser
from RpcTool.Parser.Grammar.RemoteCallLexer import RemoteCallLexer
from RpcTool.Parser.Visitors.IncludeVisitor import IncludeVisitor
from RpcTool.Parser.Visitors.ServiceVisitor import ServiceVisitor
from RpcTool.Parser.Visitors.TypeVisitor import ExceptionVisitor, EnumerationVisitor, StructureVisitor
from RpcTool.Parser.Visitors.ValidationVisitor import ValidationVisitor
from RpcTool.CodeGeneration.CppGenerator import CppGenerator
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
        documents.append(RpcDocument(name, tree))

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
    parser.add_argument('-p', '--project-name', required=True, help='The name of the project.')
    args = parser.parse_args()

    documents = LoadRpcFiles(args.input_directory)
    CreateModels(documents)
    generator = CppGenerator(documents, args.output_directory, args.project_name)
    generator.render()
