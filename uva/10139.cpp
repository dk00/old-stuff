#include<cstdlib>
long long Rand(){return rand()*(1ll<<45)+rand()*(1ll<<30)+rand()*(1ll<<15)+rand();}
long long mul(long long a,long long b,long long m)
{
    long long i,res=0;
    for(i=1;i<=b;i*=2,(a*=2)%=m)
        if(b&i)(res+=a)%=m;
    return res;
}
int pow(long long n, long long k,int m)
{
    if(k==0)return 1;
    if(k%2==1)
        return n*pow(n,k-1,m)%m;
    n=pow(n,k/2,m);
    return n*n%m;
}
bool witness(int a,int n)
{
    int x,y,u,t;
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
bool isPrime(int n,int s=25)
{
    if(n-1>=2 && witness(2,n))return 0;
    if(n-1>=3 && witness(3,n))return 0;
    if(n-1>=7 && witness(7,n))return 0;
    if(n-1>=61 && witness(61,n))return 0;
    if(n-1>=24251 && witness(24251,n))return 0;
    return 1;
}
int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}

namespace g{int abs(int x){return x<0?-x:x;}}
int _c=1;
int _f(long long x,int n){return(x*x%n+_c)%n;}
int go(int n)
{
    int x,y,d=1;
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
void factor(int n,int& fn,int s[])
{
    int x;
    while(n>1 && n%2==0)
        s[fn++]=2,n/=2;
    srand(n^s[0]);
    while(!isPrime(n))
    {
        for(_c=1,x=n;x==n;_c=1+Rand()%(n-1))x=go(n);
        if(x<0)break;
        n/=x;
        factor(x,fn,s);
    }
    if(n>1)s[fn++]=n;
}
#include<cstdio>
main()
{
    int i,j,k,n,m,x,s[99];
    while(scanf("%d %d",&m,&x)==2)
    {
        printf("%d ",x);
        factor(x,n=0,s);
        for(i=0;i<n;i+=j)
        {
            for(j=m,k=0;j>0;k+=(j/=s[i]));
            for(j=0;i+j<n && s[i+j]==s[i];j++);
            if(j>k)break;
        }
        if(i<n)printf("does not divide %d!\n",m);
        else printf("divides %d!\n",m);
    }
}
