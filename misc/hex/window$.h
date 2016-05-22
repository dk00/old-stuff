#ifndef Window$
#define Window$

// Console Functions

void coninit();
void loc(char,char);
void color(short);
void setcur(char a=0);
enum {Back=8,Tab=9,Enter=13,Esc=27,Spc=32,Up=328,Left=331,Right=333,Down=336,Del=339};
short inkey();
short waitkey();
void printf(char,char,short,const char[],...);

// Other
char setstdio(char *in="con",char *out="con");
void *Run(char *,char inherit=0);
void Kill(void *);
int Status(void *);
void sleep(int);
inline void Wait(void * x){while(Status(x)<0)sleep(5);}
#endif
