%{
	#include<stdio.h>
	#include<string>
	#include"db.h"
  using namespace std;
  #define YYSTYPE const char* 
  int yyparse(void);
  extern "C" {    
    int yylex(void);  
    int yywrap(){ return 1;}
  }
	extern int lineno;
	int yyerror(char*);
	extern DB myDB;
	Item tmpItem;
	PlayList tmpPlayList("");
%}
%token TITLE ARTIST FILENAME PLAYLIST ITEM ID VAL

%%
DataBase    : Blocks;

Blocks       : /*empty*/
	          | Blocks Item
            | Blocks List
	          ;

Item        : '{' 
              { tmpItem = Item(); } 
              AttributeList '}' 
              { myDB += tmpItem; } 
              TagList
            ;

TagList     : /*empty*/
            | ID 
              { myDB.setTag(tmpItem, $1); } 
              TagTail
            ;

TagTail	    : /*empty*/
          	| ',' ID 
              { myDB.setTag(tmpItem, $2); } 
              TagTail
          	; 
AttributeList	: /*empty*/
	            | AttributeList Attribute
          		;
Attribute	  : TITLE VAL     { tmpItem.title = $2; }
	          | ARTIST VAL    { tmpItem.artist = $2;}
        		| FILENAME VAL  { tmpItem.filename = $2;}
        		;

List        : PLAYLIST VAL 
            { tmpPlayList = PlayList($2); } 
            '{' ListContent '}' 
        	  { myDB += tmpPlayList;}
	          ;

ListContent	: /*empty*/
	          | ListContent ListItem
		        ;

ListItem	  : ITEM VAL 
		        { tmpPlayList += myDB.getId($2); }
        		| ITEM ID 
  {
    const vector<int>& tmpVector = myDB.getTagId($2);
		for(int i=0;i<tmpVector.size();++i)
	  	tmpPlayList += tmpVector[i];
	}
		        ;
%%
int yyerror(char *msg) {
  printf("Fail (around line  %d) \n", lineno);
}

