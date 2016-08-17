#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
long long Rand()
{
    return rand()*(1ll<<48)+rand()*(1ll<<32)+rand()*(1ll<<16)+rand();
}
long long mul(long long a,long long b,long long m)
{
    long long i,res=0;
    for(i=1;i<=b;i*=2,(a*=2)%=m)
        if(b&i)(res+=a)%=m;
    return res;
}
long long pow(long long n,long long k,long long m)
{
    if(k==0)return 1;
    if(k%2==1)
        return mul(n,pow(n,k-1,m),m);
    n=pow(n,k/2,m);
    return mul(n,n,m);
}
bool witness(long long a,long long n)
{
    long long x,y,u,t;
    for(u=n-1,t=0;u%2==0;u/=2,t++);
    x=pow(a,u,n);
    while(t--)
    {
        y=x;
        x=pow(x,2,n);
        if(x==1 && y!=1 && y!=n-1)
            return 1;
    }
    return x!=1;
}
bool mr(long long n,int s=25)
{
    if(n-1>=2 && witness(2,n))return 0;
    if(n-1>=3 && witness(3,n))return 0;
    if(n-1>=7 && witness(7,n))return 0;
    if(n-1>=61 && witness(61,n))return 0;
    if(n-1>=24251 && witness(24251,n))return 0;
    if(n==46856248255981ll)return 0;
    return 1;
}
long long gcd(long long a,long long b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
namespace g{long long abs(long long x){return x<0?-x:x;}}
int _c=1;
long long _f(long long x,long long n)
{return(mul(x,x,n)+_c)%n;}
long long go(long long n)
{
    long long x,y,d=1;
        x=y=Rand()%n;
        while(d==1)
        {
            x=_f(x,n);
            y=_f(_f(y,n),n);
            d=gcd(g::abs(y-x),n);
        }
        if(d!=n)return d;
    return d;
}
void fa(long long n,int& fn,long long s[])
{
    long long x;
    while(n>1 && n%2==0)
        s[fn++]=2,n/=2;
    while(!mr(n))
    {
        for(_c=1,x=n;x==n;_c=1+Rand()%(n-1))x=go(n);
        if(x<0)break;
        n/=x;
        fa(x,fn,s);
    }
    if(n>1)s[fn++]=n;
}
main()
{
    int i,j,m;
    long long n,k,s[70];
    while(scanf("%I64d",&n)==1)
    {
        m=0;
        while(n%2==0)n>>=1;
        fa(n,m,s);
        std::sort(s,s+m);
        for(i=0,k=1;i<m;i+=j)
        {
            for(j=0;i+j<m && s[i+j]==s[i];j++);
            k*=j+1;
        }
        printf("%I64d\n",k);
    }
}
