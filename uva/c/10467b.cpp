/*
E->T->F->i
E->T->F->()
E->+-
E->T->*/
#include<cstdio>
char s[200],map[201][201];
int dt[200];
void drawh(int x,int y,char* s)
{
    for(int i=0;s[i];i++)
        map[x][y+i]=s[i];
}
void drawv(int x,int y,char *s)
{
    for(int i=0;s[i];i++)
        map[x+i][y]=s[i];
}
int find(int st,int ed)
{
    if(st==ed)
        return st;
    int p,cnt=0;
    for(p=ed;p>=st;p--)
    {
        if(s[p]=='(')cnt++;
        if(s[p]==')')cnt--;
        if(cnt)continue;
        if(s[p]=='+' || s[p]=='-')break;
    }
    if(p>=st)return p;
    for(p=ed;p>=st;p--)
    {
        if(s[p]=='(')cnt++;
        if(s[p]==')')cnt--;
        if(cnt)continue;
        if(s[p]=='*' || s[p]=='/')break;
    }
    if(p>=st)return p;
    p=find(st+1,ed-1);
    dt[p]++;
    return p;
}
 char exp[]="ETFi",_t[]="=====================================\
===================================================================\
===================================================================\
=============================";
int spn[256];
void go(int d,int tn,int st,int ed,int r)
{
    if(tn>3)
        return;
    char tmp[10];
    if(dt[r]>0)
    {
        if(tn<2)
        {
            sprintf(tmp,"%c|",exp[tn]);
            drawv(d*2,r*3,tmp);
            go(d+1,tn+1,st,ed,r);
            return;
        }
        drawv(d*2,r*3,"F|");
        drawh(d*2+1,st*3,_t+200-(r-st)*3);
        drawh(d*2+1,r*3+1,_t+200-(ed-r)*3);
        drawv(d*2+2,st*3,"(");
        drawv(d*2+2,ed*3,")");
        dt[r]--;
        go(d+1,0,st+1,ed-1,r);
        return;
    }
    int r1,r2;
    switch(s[r])
    {
    case 'i':
        sprintf(tmp,"%c",exp[tn]);
        drawv(d*2,r*3,tmp);
        if(tn<3)
            drawv(d*2+1,r*3,"|");
        go(d+1,tn+1,st,ed,r);
    break;
    case '+':case '-':case '*':case '/':
        if(tn<spn[s[r]])
        {
            sprintf(tmp,"%c|",exp[tn]);
            drawv(d*2,r*3,tmp);
            go(d+1,tn+1,st,ed,r);
            return;
        }
        r1=find(st,r-1);
        r2=find(r+1,ed);
        sprintf(tmp,"%c|%c",exp[tn],s[r]);
        drawv(d*2,r*3,tmp);
        drawh(d*2+1,r1*3,_t+200-(r-r1)*3);
        drawh(d*2+1,r*3+1,_t+200-(r2-r)*3);
        go(d+1,tn,st,r-1,r1);
        go(d+1,tn+1,r+1,ed,r2);
    break;
    }
}
main()
{
    int i,j,n;
    spn['*']=spn['/']=1;
    while(scanf("%s",s)==1)
    {
        for(i=0;i<200;i++)
            for(j=0;j<200;j++)
                map[i][j]=' ';
        for(n=0;s[n];n++)dt[n]=0;
        go(0,0,0,n-1,find(0,n-1));
        for(i=0;i<200;i++)
        {
            for(j=200;j>0 && map[i][j-1]==' ';j--);
            if(j<=0)break;
            map[i][j]=0;
            puts(map[i]);
        }
        puts("");
    }
}
