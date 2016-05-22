#ifndef Window$
#define Window$

// Console Functions

void coninit();
void loc(char,char);
void color(short);
void setcur(char a=0);
enum {Enter=13,Esc=27,Up=72,Left=75,Right=77,Down=80};
short inkey();
short waitkey();
void printf(char,char,short,const char[],...);

// Other
char setstdio(char *in="CON",char *out="CON");
void *Run(char *,char inherit=0);
void Kill(void *);
int Exist(void *);
#endif
