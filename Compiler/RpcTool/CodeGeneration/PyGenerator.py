from RpcTool.Parser.RpcDocument import RpcDocument
from RpcTool.Model.Types import ListType, MapType, SetType
from jinja2 import Template
import typing
import os
import datetime
import functools

def registerTemplateFunctions(template: Template):
    def templateFunction_isListType(t):
        return isinstance(t, ListType)
    def templateFunction_isMapType(t):
        return isinstance(t, MapType)
    def templateFunction_isSetType(t):
        return isinstance(t, SetType)
    
    template.globals["isListType"] = templateFunction_isListType
    template.globals["isMapType"]= templateFunction_isMapType
    template.globals["isSetType"] = templateFunction_isSetType

def templateFunction_include(generator, templatePath, **parameters):
    template = Template(generator._readTemplate(templatePath))
    registerTemplateFunctions(template)

    includer = functools.partial(templateFunction_include, generator)
    template.globals["include"] = includer
    
    return template.render(**parameters)

class PyGenerator:
    def __init__(self, documents: typing.List[RpcDocument], outputDirectory: str, projectName: str):
        self._documents = documents
        self._outputDirectory = outputDirectory
        self._templatePaths = os.path.dirname(os.path.realpath(__file__)) + "/Templates/py/"
        self._projectName = projectName
    
    def _readTemplate(self, name: str):
        content = ""
        with open(self._templatePaths + "/" + name, "r") as file:
            content = file.read()
        return content
    
    def _writeResult(self, name: str, content: str):
        with open(self._outputDirectory + "/" + name, "w") as file:
            file.write(content)

    def _renderServices(self):
        includer = functools.partial(templateFunction_include, self)

        for document in self._documents:
            template = Template(self._readTemplate("Service.jinja2.py"))
            template.globals["include"] = includer
            registerTemplateFunctions(template)

            result = template.render(projectName = self._projectName,
                                        generatorVersion = "0.0.0.2",
                                        generatorName = "RpcTool",
                                        generationDate = str(datetime.datetime.today()),
                                        document = document)
            self._writeResult("{0}.py".format(document.name), result)

    def render(self):
        self._renderServices()