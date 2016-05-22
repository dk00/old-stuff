%{
  #include"y.tab.hpp"
  extern int lineno;
  extern void yyerror(const char *msg);
%}
le    '<='
id    [a-zA-Z_][a-zA-Z0-9_]*
num   [0-9]+
oth   [+\-*/{}(),;!=\[\]<>]
spc   [ \t\r]+

%%

"<="      return LE;
">="      return GE;
"=="      return EQ;
"!="      return NE;
"&&"      return AND;
"||"      return OR;
int       return INT;
if        return IF;
else      return ELSE;
while     return WHILE;
continue  return CONTINUE;
break     return BREAK;
scan      return SCAN;
print     return PRINT;
{id}      {sprintf(yylval.sval, "%s", yytext); return ID;}
{num}     {sscanf(yytext, "%d", &yylval.ival); return NUM;}
{oth}     return *yytext;
{spc}     {}
\n        lineno++;
.         yyerror(yytext);

%%
