#include<ctime>
#include<cstdio>
#include"window$.h"
short _C[]={8,12,14,10,11,15,15};
void printtime(int a,int b)
{
    a=(a+999)/1000,b/=1000;
    int cl=_C[(a*6/b)>?0];
    printf(1,36,cl,"%02d:%02d:%02d       ",a/3600,a%3600/60,a%60);
}
void go(int n)
{
    printtime(n,n);
    printf(1,20,2,"Time Remaining: ");
    printf(2,20,2,"Press Space to start");
    int c;
    while((c=waitkey())!=Spc);
    printf(2,20,0,"Press Space to pause");
    int x=clock(),now=0;
    while(1)
    {
        now+=clock()-x,x=clock();
        printtime((n-now)>?0,n);
        if(now>=n)break;
        sleep(50);
    }
    printf(2,20,2,"Press any key to exit");
    c=waitkey();
}
main()
{
    coninit();
    setcur();
    char tmp[100];
    //while(1)
    {
        int h,m,s,sum;
        printf(1,20,2,"Set Time(hh mm ss):                     ");
        tmp[0]=0;
        InputBox(1,39,tmp,"0123456789");
        sscanf(tmp,"%d",&h);
        tmp[0]=0;
        InputBox(1,42,tmp,"0123456789");
        sscanf(tmp,"%d",&m);
        tmp[0]=0;
        InputBox(1,45,tmp,"0123456789");
        sscanf(tmp,"%d",&s);
        sum=1000*(h*3600+m*60+s);
        go(sum);
    }
}
