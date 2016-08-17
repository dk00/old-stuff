#include<cstdio>
#include"bigint1.h"
bigint pow(bigint n,int k)
{
    if(!k)return 1;
    if(k%2)return n*pow(n,k-1);
    n=pow(n,k/2);
    return n*n;
}
main()
{
    int n,k;
    while(scanf("%d %d",&n,&k) && n+k)
        puts(pow(n,k).tostr());
}
