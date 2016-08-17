#include<cstdio>
struct node
{
    char s;
    int l,r,h;
}s[1000];
char map[300][300],_f[]="E|T|F|i",
_t[]="========================================\
============================================================\
========================================\
============================================================";
void clear()
{
    int i,j;
    for(i=0;i<200;i++)
        for(map[i][200]=0,j=0;j<200;j++)
            map[i][j]=' ';
}
int _draw;
void drawv(int y,int x,char *s)
{
    if(_draw<1)return;
    for(int i=0;s[i];i++)
        map[x+i][y]=s[i];
}
void drawh(int y,int x,char *s)
{
    if(_draw<1)return;
    for(int i=0;s[i];i++)
        map[x][y+i]=s[i];
}
int go(int d,int st,int ed)
{
    if(st>=ed)
    {
        s[st].h=d;
        return st;
    }
    int i,cnt=0;
    char exp[100];
    for(i=ed;i>=st;i--)
    {
        if(s[i].s=='(')
            cnt++;
        if(s[i].s==')')
            cnt--;
        if(cnt)continue;
        if(s[i].s=='+' || s[i].s=='-')
        {
            sprintf(exp,"E|%c",s[i].s);
            break;
        }
    }
    if(i<st)
    for(i=ed;i>=st;i--)
    {
        if(s[i].s=='(')
            cnt++;
        if(s[i].s==')')
            cnt--;
        if(cnt)continue;
        if(s[i].s=='*' || s[i].s=='/')
        {
            sprintf(exp,"T|%c",s[i].s);
            break;
        }
    }
    if(i<st)
    {
        drawv(st*3,d*2+2,"(");
        drawv(ed*3,d*2+2,")");
        s[st].h=d;
        _draw--;
        s[st].l=go(d+1,st+1,ed-1);
        _draw++;
        if(s[s[st].l].h-s[st].h>1)
            drawv(s[st].l*3,d*2,"F|E|T|"),go(d+3,st+1,ed-1);
        else if(s[s[st].l].s=='*' || s[s[st].l].s=='/')
            drawv(s[st].l*3,d*2,"F|E|"),go(d+2,st+1,ed-1);
        else
            go(d+1,st+1,ed-1);
        s[st].r=ed;
        s[ed].l=st;
        drawv(s[st].l*3,d*2,"F|");
        drawh(st*3,d*2+1,_t+200-(s[st].l-st)*3);
        drawh(s[st].l*3+1,d*2+1,_t+200-(ed-s[st].l)*3);
        return s[st].l;
    }
    drawv(i*3,d*2,exp);
    s[i].h=d;
    s[i].l=go(d+1,st,i-1);
    if(s[s[i].l].s=='i')
    {
        if(exp[0]=='E')
            drawv(s[i].l*3,d*2+2,_f);
        else
            drawv(s[i].l*3,d*2+2,_f+2);
    }
    s[i].r=go(d+1,i+1,ed);
    if(s[s[i].r].s=='i')
    {
        if(exp[0]=='E')
            drawv(s[i].r*3,d*2+2,_f+2);
        else
            drawv(s[i].r*3,d*2+2,_f+4);
    }
    drawh(s[i].l*3,d*2+1,_t+200-(i-s[i].l)*3);
    drawh(i*3+1,d*2+1,_t+200-(s[i].r-i)*3);
    return i;
}
const char exp[]="E|T|F|i";
int q[300];
main()
{
    int i,j,k,n,max,root;
    char tmp[1000];
    while(scanf("%s",tmp)==1)
    {
        for(n=0;tmp[n];n++)
            q[n]=-1,s[n].s=tmp[n];
        clear();
        _draw=1;
        root=go(0,0,n-1);
        for(i=0;i<200;i++)
        {
            for(j=200;map[i][j-1]==' ' && j>0;j--);
            if(j<=0)break;
            map[i][j]=0;
            puts(map[i]);
        }
        puts("");
    }
}
