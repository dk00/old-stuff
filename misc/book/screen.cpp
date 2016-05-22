#include<conio.h>
#include<windows.h>
class screen
{
    void *
    short cx,cy,mx,my,nc;
public:
    screen()
    {
        con$=GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO p;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&p);
        mx=p.dwSize.Y;
        my=p.dwSize.X;
        cx=p.dwCursorPosition.Y;
        cy=p.dwCursorPosition.X;
    }
    short color(short c)
    {
        if(c<0)return nc;
        SetConsoleTextAttribute(con$,(WORD)nc=clr);
        return nc;
    }
    int getloc(short& x,short& y){x=cx,y=cy;}
    int setloc(short x,short y){SetConsoleCursorPosition(con$,(COORD){cy=y,cx=x});}
    short inkey()
    {
        short i,key=-1;
        DWORD read;
        INPUT_RECORD buf;
        PeekConsoleInput(in$,&buf,1,&read);
        if(read)
        {
            key=getch();
            if(key==224)key=getch()+256;
            if(key==0)key=getch()+128;
        }
        return key;
    }
    short waitkey()
    {
        short key=getch();
        if(key==224)key=getch()+256;
        if(key==0)key=getch()+128;
        return key;
    }
    int printf(short x,short y,short c,const char[],...)
    {
        DWORD tmp;
        if(x>=0 && y>=0)setloc(x,y);
        if(c>=0)color(c);
        va_list arg;
    	va_start(arg,s);
    	vsprintf(_res,s,arg);
    	va_end(arg);
    	for(int i=0;_res[i];i++)
    	{
            if(_res[i]!='\n')cy++;
            if(_res[i]=='\n' || cy>=my){cy=0;if(cx<mx-1)cx++;}
        }
        printf(_res);
    }
    int printf(short,short,const char[],...);
    int printf(short,const char[],...);
};

