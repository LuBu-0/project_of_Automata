
grammar pascal;

start     : 'program' ID ';' 'var' decl_list main_code EOF ;

decl_list : decl | decl decl_list ;
decl      : var_list ':' 'integer' ';' ;
var_list  : ID | ID ',' var_list ;

main_code : code_block '.' ;
code_block: 'begin' st_list 'end' ;
st_list   : statement | statement ';' st_list ;
          
statement : open_stat | close_stat ;
open_stat : o_branch;
close_stat: | assign | code_block | c_branch | in | out | repeat ;

assign    : ID ':=' expr ;
o_branch  : 'if' bool_expr 'then' open_stat | 'if' bool_expr 'then' close_stat 'else' open_stat ;
c_branch  : 'if' bool_expr 'then' close_stat | 'if' bool_expr 'then' close_stat 'else' close_stat ;
in        : 'readln' '(' ID ')' ;
out       : 'writeln' '(' expr ')' ;
repeat    : 'repeat' st_list 'until' bool_expr ;

expr      : arith_expr | bool_expr | STRING ;

arith_expr: sum_expr ;
sum_expr  : prod_expr | prod_expr ('+' | '-') sum_expr;
prod_expr : sign_val | sign_val ('*' | '/' | '%') prod_expr ;
sign_val  : arith_val | ('+' | '-') sign_val;
arith_val : NUMBER | ID | '(' arith_expr ')';

bool_expr : or_expr ;
or_expr   : and_expr | and_expr 'or' or_expr ;
and_expr  : not_expr | not_expr 'and' and_expr ;
not_expr  : bool_value | 'not' bool_value ;
bool_value: relation | '(' bool_expr ')' ;
relation  : arith_expr LT arith_expr | arith_expr LEQ arith_expr | arith_expr EQ arith_expr 
          | arith_expr NEQ arith_expr | arith_expr GEQ arith_expr | arith_expr GT arith_expr ;

EQ        : '=' ;
LT        : '<' ;
LEQ       : '<=' ;
GT        : '>' ;
GEQ       : '>=' ;
NEQ       : '<>' ;
ID        : [a-z]+ ;
NUMBER    : [0-9]+ ;
R_COMMENT : '(*' .*? '*)' -> skip ;     // .*? matches anything until the first */
C_COMMENT : '{' .*? '}' -> skip ;       // .*? matches anything until the first }
LINE_COMMENT : '//' ~[\r\n]* -> skip ;  // ~[\r\n]* matches anything but \r and \n
STRING    : '\'' (~['])* '\'' ;
WS        : [ \n\t\r]+ -> skip;
ErrorChar : . ;
