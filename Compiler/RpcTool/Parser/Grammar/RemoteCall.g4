grammar RemoteCall;

document:       .*? (statement .*?)*;
statement:      include | structure | exception | enumeration | service;
include:        Include '"' Identifier '.' Identifier '"';

structure:      Struct Identifier '{' declaration+ '}';
exception:      Exception Identifier '{' declaration+ '}';
enumeration:    Enum Identifier '{' enumerationValues '}';
enumerationValues: Identifier ('=' Number)? (',' enumerationValues)?;

service:        Service Identifier '{' function+ '}';
function:       Callback? someType Identifier '(' args? ')' (Throws '(' args ')')? (';'|',')?;

declaration:    arg ';';
args:           arg | (arg ',' args);
arg:            Number ':' someType Identifier;
someType:       listType | setType | mapType | regularType;
listType:       'list<' regularType '>';
setType:        'set<' regularType '>';
mapType:        'map<' regularType ',' regularType '>';
regularType:    Identifier ('.' Identifier)?;

Callback:       '[[callback]]';
Include:        'include';
Exception:      'exception';
Enum:           'enum';
Struct:         'struct';
Service:        'service';
Throws:         'throws';
Number:         [0-9]+ | '0x' [0-9a-f]+;
Identifier:     [a-zA-Z_][a-zA-Z0-9_]*;
WhiteSpace:     [\n\t\r ]+ -> skip;
Other:          . -> skip;
