#include<ctime>
#include<cstdlib>
inline int Rand(){return (rand()<<16)+rand();}
inline int pow(long long n,int k,int m)
{
    if(k==0)return 1;
    if(k%2==1)
        return n*pow(n,k-1,m)%m;
    n=pow(n,k/2,m);
    return n*n%m;
}
inline bool witness(int a,int n)
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
inline bool isPrime(int n,int s=25)
{
    if(n-1>=2 && witness(2,n))return 0;
    if(n-1>=3 && witness(3,n))return 0;
    if(n-1>=7 && witness(7,n))return 0;
    if(n-1>=61 && witness(61,n))return 0;
    if(n-1>=24251 && witness(24251,n))return 0;
    //if(n==46856248255981ll)return 0;
    return 1;
}
inline int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}

int c=1;
inline int f(long long x,int n){return(x*x)+c)%n;}
inline int go(int n)
{
    int x,y,d=1;
    x=y=Rand()%n;
    while(d==1)
    {
        x=f(x,n);
        y=f(f(y,n),n);
        d=gcd(abs(y-x),n);
    }
    return d;
}
inline void factor(int m,int& n,int s[])
{
    int x;
    while(m>1 && m%2==0)
        s[n++]=2,m/=2;
    srand(time(NULL));
    while(!isPrime(m))
    {
        for(c=1,x=m;x==m;c=1+Rand()%(m-1))x=go(m);
        if(x<0)break;
        m/=x;
        factor(x,n,s);
    }
    if(m>1)s[n++]=m;
}

#include<cstdio>
const int N=2000000;
int ph[N+1];
long long s[N+1];
main()
{
    int i,j,k;
    for(i=1;i<=N;i++)
        ph[i]=i;
    for(i=1;i<=N;i++)
        for(j=i*2,k=ph[i];j<=N;j+=i)
        {
            ph[j]-=ph[i];
            s[j]+=k;
            k+=ph[i];
        }
    for(i=1;i<=N;i++)
        s[i]+=s[i-1];
    while(scanf("%d",&i) && i)
        printf("%lld\n",s[i]);
}
