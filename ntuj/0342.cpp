#include<cstdio>
long long go(long long x)
{
    if(x<3)return x;
    if(x<5)return x-1;
    for(long long i=3;i*i<=x;i++)
        if(x%i==0)return x-x/i;
    if(x%2==0)return x-2;
    return x-1;
}
main()
{
    long long i,j,k,T;
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld %lld",&i,&k);
        while(k--)
        {
            for(j=i;go(j)<i;j++);
            i=j;
        }
        printf("%lld\n",i);
    }
}
