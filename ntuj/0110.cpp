#include<cstdio>
long long gcd(long long f,long long g,long long &a,long long &b)
{
    long long d;
    if(!g)
    {
        a=1,b=0;
        return f;
    }
    d=gcd(g,f%g,b,a);
    b=b-a*(f/g);
    return d;
}
long long go(long long x,long long k,long long m)
{
    k=(k%m+m)%m;
    if(k==0)return 0;
    if(x==0)return -1;
    long long a,b,d;
    d=gcd(x,m,a,b);
    if(k%d)return -1;
    a=(a%(m/d)+m/d)%(m/d);
    return k/d*a%(m/d);
}
main()
{
    long long a,b,c,d;
    while(scanf("%lld %lld %lld %lld",&a,&b,&c,&d) && a+b+c+d)
    {
        long long ans=go(c,b-a,1ll<<d);
        if(ans>=0)
            printf("%lld\n",ans);
        else
            puts("FOREVER");
    }
}
