#include<ctime>
#include<cstdio>
#include"bigint1a.h"
const int N=10000;
bigint res,r;
bigint pow1()
{
    r=N;
    res=1;
    for(int i=1;i<=N;i*=2,r*=r)
        if(i&N)res*=r;
    //puts(res.tostr());
}
bigint pow2()
{
    r=N;
    res=1;
    for(int i=1;i<=N;i++)
        res*=r;
    //puts(res.tostr());
}
main()
{
    int start;
    start=clock();
    pow1();
    printf("%d\n",clock()-start);
    start=clock();
    pow2();
    printf("%d\n",clock()-start);
    scanf(" ");
}
