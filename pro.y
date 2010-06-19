%{
	#include<stdio.h>
	#include<string>
	#include"db.c"
        using namespace std;
        #define YYSTYPE char* 
	extern int yyparse();
	extern int yylex();
	extern int yywrap();
	extern int lineno;
	int yyerror(char*);
	DB myDB;
	Item tmpItem;
	PlayList tmpPlayList("");
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

itemStmt : '{' { tmpItem = Item(); } itemAttributeA '}' { myDB += tmpItem; } tag
	      
	 ;

tag : /*empty*/
    | ID { myDB.setTag(tmpItem, $1); } dotTag
    ;

dotTag	: /*empty*/
	| ',' ID { myDB.setTag(tmpItem, $2); } dotTag
	; 

itemAttributeA	: /*empty*/
	        | itemAttributeA itemAttribute
		;
itemAttribute	: TITLE VAL { tmpItem.title = $2; }
	        | ARTIST VAL { tmpItem.artist = $2;}
		| FILENAME VAL { tmpItem.filename = $2;}
		;


listStmt : PLAYLIST VAL { tmpPlayList = PlayList($2); } '{' listAttributeA '}' 
	   { myDB.addPlayList(tmpPlayList);}
	 ;

listAttributeA	: /*empty*/
	        | listAttributeA listAttribute
		;

listAttribute	: ITEM VAL 
		  {
		    tmpPlayList += myDB.getId($2); 
		  }
		| ITEM ID 
		  {
		    vector<int> tmpVector = myDB.getTagId($2);
		    for(int i=0;i<tmpVector.size();++i)
		      tmpPlayList += tmpVector[i];
		  }
		;
%%
int main()
{
  yyparse();
  //myDB.showAll();
  return 0;
}
int yyerror(char *msg)
{
  printf("Fail (around line  %d) \n", lineno);
}

