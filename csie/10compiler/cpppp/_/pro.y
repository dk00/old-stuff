%{
	#include<stdio.h>
        typedef char* string;
        #define YYSTYPE string
	extern int lineno;
%}
%token TITLE ARTIST FILENAME PLAYLIST ITEM ID VAL

%%
program : blockStmtA;

blockStmtA  : /*empty*/
	    | blockStmtA blockStmt
	    ;

blockStmt  : itemStmt 
	   | listStmt
	   ;

itemStmt : tag '{' itemAttributeA '}'
	 ;

tag : ID dotTag
    ;

dotTag	: /*empty*/
	| ',' ID dotTag
	; 

itemAttributeA	: /*empty*/
	        | itemAttributeA itemAttribute
		;
itemAttribute	: TITLE VAL { printf("title: %s\n", $2);}
	        | ARTIST VAL { printf("artist: %s\n", $2);}
		| FILENAME VAL { printf("filename: %s\n", $2);}
		;


listStmt : PLAYLIST VAL '{' listAttributeA '}'
	 ;

listAttributeA	: /*empty*/
	        | listAttributeA listAttribute
		;

listAttribute	: ITEM VAL { printf("add '%s' to list\n", $2); }
		| ITEM ID { printf("add item with tag %s\n", $2); }
		;
%%
int main()
{
  yyparse();
  return 0;
}
int yyerror(char *msg)
{
  printf("Fail (around line  %d) \n", lineno);
}

