#include<cstdio>
long long gcd(long long a,long long b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
long long go(long long x,long long k,long long m)
{
    k=(k%m+m)%m;
    if(k==0)return 0;
    if(!x || k%gcd(x,m))return -1;
    long long i,t,tmp;
    for(i=x,t=1;i!=0;)
    {
        if(i<k)
        {
            tmp=(k-i+x-1)/x;
            i=(i+x*tmp)%m;
            t+=tmp;
        }
        if(i==k)return t;
        if(i<m)
        {
            tmp=(m-i+x-1)/x;
            i=(i+x*tmp)%m;
            t+=tmp;
        }
    }
    return -1;
}
main()
{
    long long a,b,c,d;
    while(scanf("%I64d %I64d %I64d %I64d",&a,&b,&c,&d) && a+b+c+d)
    {
        long long ans=go(c,b-a,1ll<<d);
        if(ans>=0)
            printf("%I64d\n",ans);
        else
            puts("FOREVER");
    }
}
