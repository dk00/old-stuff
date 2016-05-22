#include"window$.h"
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
int exist(char name[])
{
    FILE *fp=fopen(name,"rb");
    if(!fp)return 0;
    fclose(fp);
    return 1;
}
void error(char *mes=0)
{
    if(mes)puts(mes);
    exit(0);
}
void printtime(int x,int y,int now,int lim)
{
    int c=8;//15,11,10,14,12,8
    if(now*5<5*lim)c=12;
    if(now*5<4*lim)c=14;
    if(now*5<3*lim)c=10;
    if(now*5<2*lim)c=11;
    if(now*5<1*lim)c=15;
    setloc(x,y);
    color(c);
    printf("%d.%03d",now/1000,now%1000);
}
char tmp1[999999],tmp2[999999];
int cmp(char o1[],char o2[])
{
    int a=1,b=1;
    FILE *f1=fopen(o1,"r"),*f2=fopen(o2,"r");
    while(1)
    {
        a=fscanf(f1,"%s",tmp1);
        b=fscanf(f2,"%s",tmp2);
        if(a!=b)return 1;
        if(a<0)break;
        if(strcmp(tmp1,tmp2))return 1;
    }
    return 0;
}
char judge(char exe[],char in[],char out[],int tl)
{
    if(!exist(in))
    {
        puts("Input file does not exist");
        return 0;
    }
    if(!exist(out))
    {
        puts("Input file does not exist");
        return 0;
    }
    int x,y,now,start,stat;
    void *proc;
    coninit();
    getloc(x,y);
    printf("%d %d\n",x,y);
    scanf(" ");
//    printtime(x,y,0,tl);
    setstdio(in,"out");
    start=clock();
    proc=Run(exe,1);
    setstdio();
    while((stat=Status(proc))==-1)
    {
        now=clock()-start;
        //printtime(x,y,now,tl);
        if(now>tl)
        {
            Kill(proc);
            printtime(x,y,now,tl);
            color(10);
            puts(" Time Limit Excceed");
            return 0;
        }
        sleep(5);
    }
    printtime(x,y,now,tl);
    if(stat)
    {
        color(11);
        puts(" Runtime Error");
        return 0;
    }
    if(cmp("out",out))
    {
        color(10);
        puts(" Wrong Answer");
        return 0;
    }
    color(12);
    puts(" Accepted");
    return 1;
}
char in[999],out[999],ifmt[999],ofmt[999],tmp[99999];
int sc[999];
main(int m,char **c)
{
    int i,n,tl,sum;
    coninit();
    int x,y;
    getloc(x,y);
    printf("%d %d\n",x,y);
    if(m!=3)return 0;
    sprintf(tmp,"%s.cpp",c[2]);
    if(!exist(c[1]) || !exist(tmp))
        error("Judge script or source file doesn't exist");
    setstdio(c[1]);
    if(scanf("%d %d %s %s",&n,&tl,ifmt,ofmt)!=4)
        error("Judge script format is not correct");
    for(i=1;i<=n;i++)
        if(scanf("%d",sc+i)<0)
            error("Judge script format is not correct");
    setstdio();
    sprintf(tmp,"del %s.exe",c[2]);
    Wait(Run(tmp));
    sprintf(tmp,"g++ %s.cpp -O2 -o %s",c[2],c[2]);
    Wait(Run(tmp));
    sprintf(tmp,"%s.exe",c[2]);
    if(!exist(tmp))
        error("Compile rrror.");
    for(i=1,sum=0;i<=n;i++)
    {
        color(7);
        printf("Test %02d: ",i);
        sprintf(in,ifmt,i);
        sprintf(out,ofmt,i);
        if(judge(tmp,in,out,tl))
            sum+=sc[i];
    }
    color(7);
    printf("Score: %d\n",sum);
    
}
