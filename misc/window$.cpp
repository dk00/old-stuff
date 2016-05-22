#include<cstdio>
#include<cstdarg>
#include<conio.h>
#include<windows.h>
// console Functions

void *in$,*con$;
char con;
void coninit(){in$=GetStdHandle(STD_INPUT_HANDLE),
con$=GetStdHandle(STD_OUTPUT_HANDLE);}
void loc(char x,char y){SetConsoleCursorPosition(con$,(COORD){y,x});}
void color(short clr){SetConsoleTextAttribute(con$,(WORD)clr);}
void setcur(char visible=0){
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible=visible;
    cci.dwSize=2;
    SetConsoleCursorInfo(con$,&cci);
}
void sleep(int x){Sleep(x);}
enum {Back=8,Tab=9,Enter=13,Esc=27,Spc=32,Up=328,Left=331,Right=333,
Down=336,Del=339,PgUp=329,PgDn=337};
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
char _res[300];
void printf(char x,char y,short c,const char s[],...)
{
    DWORD tmp;
    if(x>=0 && y>=0)loc(x,y);
    if(c>=0)color(c);
    va_list arg;
	va_start(arg,s);
	vsprintf(_res,s,arg);
	va_end(arg);
	WriteConsole(con$,_res, strlen(_res),&tmp,&tmp);
}

// Other
char setstdio(char *in,char *out)
{
    FILE *fin,*fout;
    if(in)
    {
        fin=fopen(in,"r");
        if(!fin)return 0;
        fclose(fin);
    }
    freopen(in,"r",stdin);
    freopen(out,"w",stdout);
    coninit();
    return 1;
}
void *Run(char *exec,char inherit=0)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
	ZeroMemory(&si,sizeof(si));
	ZeroMemory(&pi,sizeof(pi));
	si.cb=sizeof(si);
    CreateProcess(0,exec,0,0,inherit,0,0,0,&si,&pi);
    return pi.hProcess;
}
void Kill(void *proc){TerminateProcess(proc,0);}
int Status(void *proc)
{
    DWORD tmp=0;
    GetExitCodeProcess(proc,&tmp);
    if(tmp==STILL_ACTIVE)return -1;
    return tmp;
}

void InputBox(char sx,char sy,char buf[],char ac[],short col)
{
    int i,j,n,c,py=sy;
    char u[128],pre[999];
    strcpy(pre,buf);
    for(i=0;i<128;i++)
        u[i]=0;
    if(ac)
        for(i=0;ac[i];i++)
            u[ac[i]]=1;
    else
        for(i=0;i<256;i++)
            u[i]=1;
    setcur(1);
    printf(sx,sy,col,buf);
    for(i=0;buf[i];i++,sy++);
    n=i;
    while(1)
    {
        buf[n+1]=0;
        c=waitkey();
        if(c==Enter)break;
        if(c==Esc)
        {
            strcpy(buf,pre);
            printf(sx,sy=py,-1,buf);
            for(i=0;buf[i];i++,sy++);
            n=i;
        }
        if(i>0 && c==Back)
        {
            for(j=--i;j<=n;j++)
                buf[j]=buf[j+1];
            buf[--n]=' ';
            printf(sx,--sy,-1,buf+i);
            buf[n]=0;
            loc(sx,sy);
        }
        if(i>0 && c==Left)
            i--,loc(sx,--sy);
        if(i<n && c==Right)
            i++,loc(sx,++sy);
        if(i<n && c==Del)
        {
            for(j=i;j<=n;j++)
                buf[j]=buf[j+1];
            buf[--n]=' ';
            printf(sx,sy,-1,buf+i);
            buf[n]=0;
            loc(sx,sy);
        }
        if(c<128 && u[c])
        {
            for(j=++n;j>i;j--)
                buf[j]=buf[j-1];
            buf[i]=c;
            printf(-1,sy++,-1,buf+i++);
            loc(sx,sy);
        }
    }
    setcur(0);
}
