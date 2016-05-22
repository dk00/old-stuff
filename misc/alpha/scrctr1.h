#ifndef SCRCTR1_H
#define SCRCTR1_H
#include<conio.h>
#include<cstdio>
#include<cstring>
#include<cstdarg>
#include<windows.h>
HANDLE hin,hout;
enum {Black=0,Blue,Green,Cyan,Red,Magenta,Brown,lGray,dGray,lBlue,lGreen,
    lCyan,lRed,lMagenta,Yellow,White};
enum {Enter=13,Esc=27,Space=32,F1=59,F2,F3,F4,F5,F6,F7,F8,F9,F10,
    Up=72,Left=75,Right=77,Down=80};
inline void coninit()
{
	hin=GetStdHandle(STD_INPUT_HANDLE);
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
}
inline void color(short fc,short bc)
{SetConsoleTextAttribute(hout,fc|(bc<<4));}
inline int inkey()
{
    if(kbhit())return getch();
    return -1;
}
inline void locate(short x,short y){
    SetConsoleCursorPosition(hout,(COORD){y,x});
}
inline int cprintf(char *s,...)
{
	va_list arg;
	char res[300];
	va_start(arg,s);
	vsprintf(res,s,arg);
	va_end(arg);
	_cprintf(res);
}
inline int cprintf(short x,short y,char *s,...)
{
    locate(x,y);
	va_list arg;
	char res[300];
	va_start(arg,s);
	vsprintf(res,s,arg);
	va_end(arg);
	_cprintf(res);
}
inline void cls(short x1=0,short y1=0,short x2=24,short y2=79)
{
    color(lGray,Black);
    short i;
    char buf[300];
    for(i=y1;i<=y2;i++)buf[i-y1]=' ';
    buf[i]=0;
    for(;x1<=x2;x1++)
        cprintf(x1,y1,buf);
}
#endif
