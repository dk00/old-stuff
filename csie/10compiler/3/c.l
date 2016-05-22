%{
  #include"y.tab.h"
  extern int lineno;
  extern void yyerror(const char *msg);
%}
id    [a-zA-Z_][a-zA-Z0-9_]*
num   [0-9]*
sign  [+/-]
op    [*/]
bop   "&&"|"||"
cmp   "=="|"<="|">="|"!="|[<>]
oth   [{}(),;!=\[\]]
cntl  continue|break

%%

int       return INT;
if        return IF;
else      return ELSE;
while     return WHILE;
{cntl}    return CNTL;
scan      return SCAN;
print     return PRINT;
{id}      return ID;
{num}     return NUM;
{sign}    return SIGN;
{op}      return OP;
{bop}     return BOP;
{cmp}     return CMP;
{oth}     {puts(yytext);return *yytext;}
\n        lineno++;
.         yyerror(*yytext);

%%
