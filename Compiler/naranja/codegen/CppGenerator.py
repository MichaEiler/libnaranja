from naranja.parser.Document import Document
from naranja.model.Types import ListType, RegularType, Argument
from jinja2 import Template
import typing
import os
import datetime
import functools
import string
import random

def registerTemplateFunctions(generator, template: Template):
    def templateFunction_isListType(t):
        return isinstance(t, ListType)
    def templateFunction_isEnum(generator, documentName: str, arg: RegularType):
        return generator._templateHelper_isEnum(documentName, arg)
    def templateFunction_getStructureArgs(generator, documentName: str, arg: RegularType):
        return generator._templateHelper_getStructureArgs(documentName, arg)
    def templateFunction_isPrimitive(arg: RegularType):
        return (not isinstance(arg, ListType)) and (arg.namespace is None) and arg.isPrimitive()
    def templateFunction_isEmpty(t):
        return (t is None) or t == ""
    def templateFunction_len(t):
        return len(t)
    def templateFunction_randStr():
        letters = string.ascii_lowercase
        return ''.join(random.choice(letters) for i in range(10))
    
    template.globals["isListType"] = templateFunction_isListType
    template.globals["isEnum"] = functools.partial(templateFunction_isEnum, generator)
    template.globals["getStructureArgs"] = functools.partial(templateFunction_getStructureArgs, generator)
    template.globals["isEmpty"] = templateFunction_isEmpty
    template.globals["isPrimitive"] = templateFunction_isPrimitive
    template.globals["len"] = templateFunction_len
    template.globals["randStr"] = templateFunction_randStr

def templateFunction_include(generator, templatePath, **parameters):
    template = Template(generator._readTemplate(templatePath))
    registerTemplateFunctions(generator, template)

    includer = functools.partial(templateFunction_include, generator)
    template.globals["include"] = includer
    
    return template.render(**parameters)

class CppGenerator:
    def __init__(self, documents: typing.List[Document], outputDirectory: str):
        self._documents = documents
        self._outputDirectory = outputDirectory
        self._templatePaths = os.path.dirname(os.path.realpath(__file__)) + "/templates/cpp17/"
    
    def _readTemplate(self, name: str):
        content = ""
        with open(self._templatePaths + "/" + name, "r") as file:
            content = file.read()
        return content
    
    def _templateHelper_isEnum(self, documentName: str, arg: RegularType):
        documentName = documentName if arg.namespace is None else arg.namespace
        for document in self._documents:
            if document.name == documentName:
                for enumeration in document.enumerations:
                    if enumeration.name == arg.name:
                        return True
        return False
    
    def _templateHelper_getStructureArgs(self, documentName: str, arg: RegularType):
        documentName = documentName if arg.namespace is None else arg.namespace
        for document in self._documents:
            if document.name == documentName:
                return document.getStructureArgs(arg.name)
        raise RuntimeError("Could not resolve structure members (Unknown type).")

    def _writeResult(self, name: str, content: str):
        with open(self._outputDirectory + "/" + name, "w") as file:
            file.write(content)

    def _renderServices(self):
        includer = functools.partial(templateFunction_include, self)

        for document in self._documents:
            template = Template(self._readTemplate("Service.hpp.jinja2"))
            template.globals["include"] = includer
            registerTemplateFunctions(self, template)

            result = template.render(generatorVersion = "0.0.0.3",
                                        generatorName = "NaranjaTool",
                                        generationDate = str(datetime.datetime.today()),
                                        document = document)
            self._writeResult("{0}.hpp".format(document.name), result)


            template = Template(self._readTemplate("Service.cpp.jinja2"))
            template.globals["include"] = includer
            registerTemplateFunctions(self, template)

            result = template.render(generatorVersion = "0.0.0.3",
                                        generatorName = "NaranjaTool",
                                        generationDate = str(datetime.datetime.today()),
                                        document = document)
            self._writeResult("{0}.cpp".format(document.name), result)

    def render(self):
        self._renderServices()

