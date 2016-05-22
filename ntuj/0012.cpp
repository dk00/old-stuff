#include<cstdio>
long long mul(long long a,long long b,long long m)
{
    long long i,res=0;
    for(i=1;i<=b;i*=2,(a*=2)%=m)
        if(b&i)res+=a;
    return res;
}
long long cube(long long n,long long m){return mul(mul(n,n,m),n,m);}
main()
{
    int T;
    long long i,j,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        for(i=10,j=0;i<=n*10;i*=10)
            while(cube(j,i)%i!=n%i)j+=i/10;
        printf("%lld\n",j);
    }
}
