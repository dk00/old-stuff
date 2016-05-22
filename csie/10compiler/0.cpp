#include<stdio.h>
typedef struct {
  const char str[9];
  unsigned code;
} Token;
const int kNumTokens = 36, kNumStates = 1024;
const char *Tokens[]={"*","+","-","/","%","&&","||","!","<",">","<=",">=","==","!=","&","|","^","(",")","[","]","{","}",",",";","=","char","int","void","if","else","while","for","continue","break","return"};
const Token kTokens[kNumTokens]={
  {"*",42 },
  {"+",43 },
  {"-",45 },
  {"/",47 },
  {"%",37 },
  {"&&",265 },
  {"||",266 },
  {"!",33 },
  {"<",60 },
  {">",62 },
  {"<=",261 },
  {">=",262 },
  {"==",263 },
  {"!=",264 },
  {"&",38 },
  {"|",124 },
  {"^",94 },
  {"(",40 },
  {")",41 },
  {"[",91 },
  {"]",93 },
  {"{",123 },
  {"}",125 },
  {",",44 },
  {";",59 },
  {"=",61 },
  {"char",268 },
  {"int",269 },
  {"void",270 },
  {"if",271 },
  {"else",272 },
  {"while",273 },
  {"for",274 },
  {"continue",275 },
  {"break",276 },
  {"return",277 }
};
enum TokenCode {
  IDENTIFIER = 258,
  INTEGER = 259,
  STRING = 260
};

int state[kNumStates][256] = {0};

void Init() {
  int i,j,k,num_states = 300;
  for (i = 0; i < kNumTokens; i++) {
    /*const char *str = kTokens[i].str;
    for (j = k = 0; str[j]; j++);*/


  }
}

main(){
  int i;
  for (i = 0; i < kNumTokens; i++) {
    printf("%d,",kTokens[i].code);

  }
}
