grammar pascal;

start     : 'program' ID ';' 'var' decl_list main_code EOF ;

decl_list : decl | decl decl_list ;
decl      : id_list ':' 'integer' ';' ;
id_list   : ID | ID ',' id_list ;

main_code : 'begin' st_list 'end' '.' ;
code_block: statement | 'begin' st_list 'end' ;
st_list   : statement ';' | statement ';' st_list  ;
          
statement : assign | branch | out | loop | in ;

assign    : ID ':=' expr ;
out       : 'writeln' '(' expr ')' | 'writeln' '(' STRING ')' ;
in        : 'readln' '(' ID ')' ;
branch    : 'if' guard 'then' code_block 
          | 'if' guard 'then' code_block 'else' code_block;
loop      : 'repeat' st_list 'until' guard ;
expr      : expr MOD expr | expr DIV expr | expr MULT expr | expr MINUS expr | expr PLUS expr |
          | '(' expr ')' | NUMBER | ID ;
guard     : NOT guard | guard AND guard | guard OR guard | '(' guard ')' | relation ;
relation  : expr LT expr | expr LEQ expr | expr EQ expr 
          | expr NEQ expr | expr GEQ expr | expr GT expr ;

PLUS      : '+' ;
MINUS     : '-' ;
MULT      : '*' ;
DIV       : '/' ;
MOD       : '%' ;

AND       : 'and' ;
OR        : 'or' ;
NOT       : 'not' ;

EQ        : '=' ;
LT        : '<' ;
LEQ       : '<=' ;
GT        : '>' ;
GEQ       : '>=' ;
NEQ       : '<>' ;
ID        : [a-z]+ ;
NUMBER    : [0-9]+ ;
STRING    : '\'' .*? '\'';
R_COMMENT : '(*' .*? '*)' -> skip ;     // .*? matches anything until the first */
C_COMMENT : '{' .*? '}' -> skip ;       // .*? matches anything until the first }
LINE_COMMENT : '//' ~[\r\n]* -> skip ;  // ~[\r\n]* matches anything but \r and \n
WS        : [ \n\t\r]+ -> skip;
ErrorChar : . ;
