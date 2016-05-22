#include<cstdio>
int m;
long long go(long long n)
{
    if(n<m)return n;
    return n-go(n/m);
}
main()
{
    int T;
    long long n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld %d",&n,&m);
        printf("%lld\n",go(n));
    }
}
