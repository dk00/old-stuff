#ifndef ita_h
#define ita_h
#include<ctime>
#include<cstdlib>
#ifndef inttype
#define inttype int
#endif
inttype Rand()
{
    return rand()*(1ll<<48)+rand()*(1ll<<32)+rand()*(1ll<<16)+rand();
}
#if inttype!=int
inttype mul(inttype a,inttype b,inttype m)
{
    inttype i,res=0;
    for(i=1;i<=b;i*=2,(a*=2)%=m)
        if(b&i)(res+=a)%=m;
    return res;
}
#else
inline int mul(long long a,int b,int m){return a*b%m;}
#endif
inttype pow(inttype n,inttype k,inttype m)
{
    if(k==0)return 1;
    if(k%2==1)
        return mul(n,pow(n,k-1,m),m);
    n=pow(n,k/2,m);
    return mul(n,n,m);
}
bool witness(inttype a,inttype n)
{
    inttype x,y,u,t;
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
bool isPrime(inttype n,int s=25)
{
    if(n-1>=2 && witness(2,n))return 0;
    if(n-1>=3 && witness(3,n))return 0;
    if(n-1>=7 && witness(7,n))return 0;
    if(n-1>=61 && witness(61,n))return 0;
    #if(intttype!=int)
    if(n-1>=24251 && witness(24251,n))return 0;
    if(n==46856248255981ll)return 0;
    #endif
    return 1;
}
inttype gcd(inttype a,inttype b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}

namespace g{inttype abs(inttype x){return x<0?-x:x;}}
int _c=1;
inttype _f(inttype x,inttype n)
{return(mul(x,x,n)+_c)%n;}
inttype go(inttype n)
{
    inttype x,y,d=1;
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
void factor(inttype n,int& fn,inttype s[])
{
    inttype x;
    while(n>1 && n%2==0)
        s[fn++]=2,n/=2;
    srand(time(NULL));
    while(!isPrime(n))
    {
        for(_c=1,x=n;x==n;_c=1+Rand()%(n-1))x=go(n);
        if(x<0)break;
        n/=x;
        factor(x,fn,s);
    }
    if(n>1)s[fn++]=n;
}
#endif
