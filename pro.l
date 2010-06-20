%{
	#define YYSTYPE const char*
  #include "y.tab.hpp"
  #include <stdio.h>
  #include <string.h>
  int lineno = 1;
%}
char [A-Za-z]
num [0-9]
%%
"/*"("/")?([^/]|[^*]"/")*"*/" {}
[ \t]  { }
\n     { }
title return TITLE; 
artist  return ARTIST;
filename return FILENAME;
playlist return PLAYLIST;
item return ITEM;
({char}|{num})* {
  yylval = strdup(yytext); 
  return ID; 
}
\'([^\'])*\' {
  yylval = strndup(yytext+1,strlen(yytext)-2);
  return VAL;
}
.       return yytext[0]; 
%%
