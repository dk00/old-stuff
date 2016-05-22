#include<ctime>
#include<cstdlib>
#define inttype long long
inttype Rand()
{
    return rand()*(1ll<<48)+rand()*(1ll<<32)+rand()*(1ll<<16)+rand();
}
inttype mul(inttype a,inttype b,inttype m)
{
    inttype i,res=0;
    for(i=1;i<=b;i*=2,(a*=2)%=m)
        if(b&i)(res+=a)%=m;
    return res;
}
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
    if(n-1>=24251 && witness(24251,n))return 0;
    if(n==46856248255981ll)return 0;
    return 1;
}
#include<cstdio>
main()
{
    int n;
    while(scanf("%d",&n)==1 && n)
    {
        if(isPrime(n))
            puts("質數");
        else
            puts("非質數");
    }
}
