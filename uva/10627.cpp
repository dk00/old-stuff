#include<cmath>
#include<cstdio>
long long gcd(long long a,long long b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
main()
{
    long long l,v,u,t,k;
    while(scanf("%lld %lld %lld %lld",&l,&v,&u,&t) && l)
    {
        if(v+u==0)
        {
            puts("0");
            continue;
        }
        if(v<u)k=v,v=u,u=k;
        k=v/gcd(u,v);
        if(v==u ||(k+u/gcd(u,v))%2==0)k=0;
        else k=(v*t/l+k)/2/k;
        if(v*t/l%2==u*t/l%2 && v*t%l+u*t%l>=l)k--;
        if(v*t/l%2!=u*t/l%2 && v*t%l>=u*t%l)k--;
        printf("%lld\n",v*t/l-k);
    }
}
