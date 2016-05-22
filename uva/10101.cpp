#include<cstdio>
int u[]={100,10,100,100};
char b[][6]={"kuti","shata","hajar","lakh"};
bool go(long long n,int d)
{
    if(!n && !d)printf(" 0");
    if(n<1)return 0;
    int c=go(n/u[d%4],d+1);
    if(n%u[d%4])
    {
        printf(" %d",n%u[d%4]);
        if(d)printf(" %s",b[d%4]);
    }
    else if(c && d%4==0 && d)
        printf(" %s",b[d%4]);
    return(c+n%u[d%4]);
}
main()
{
    int C=1;long long n;
    while(scanf("%lld",&n)==1)
    {
        printf("%4d.",C++);
        go(n,0);
        puts("");
    }
}
