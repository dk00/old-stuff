%{
  #include<stdio.h>
  int lineno = 1,error = 0;
%}

%token    ID
%token    NUM
%token    INT
%token    IF
%token    ELSE
%token    WHILE
%token    CNTL
%token    SCAN
%token    PRINT
%token    SIGN
%token    OP
%token    BOP
%token    CMP

%%
blockStmt : '{' varDecl stmts '}'
          ;
varDecl   :
          | varDecl type list ';'
          ;
type      : INT 
          | INT '[' NUM ']'
          ;
list      : ID
          | list ',' ID
          ;
var       : ID
          | ID '[' arithExpr ']'
          ;
stmts     :
          | stmts stmt
          ;          
stmt      : blockStmt
          | var '=' arithExpr ';'
          | IF '(' boolExpr ')' blockStmt
          | IF '(' boolExpr ')' blockStmt ELSE blockStmt
          | WHILE '(' boolExpr ')' blockStmt
          | CNTL ';'
          | SCAN '(' varList ')' ';'
          | PRINT '(' expList ')' ';'
          ;
varList   : var
          | varList ',' var
          ;
expList   : arithExpr
          | expList ',' arithExpr
          ;
arithExpr : var
          | NUM
          | '(' arithExpr ')'
          | SIGN arithExpr
          | arithExpr OP arithExpr
          | arithExpr SIGN arithExpr          
          ;
boolExpr  : arithExpr CMP arithExpr
          | boolExpr BOP boolExpr
          | '!' boolExpr
          ;
%%

extern void yyerror(char *msg) {
  error = lineno;
}

int main() {
  yyparse();
  if (error > 0)
    printf("Fail (around line %d)\n",error);
  else
    puts("Pass");
}
