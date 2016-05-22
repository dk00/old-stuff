#define inttype long long
inline int mul(long long a,int b,int m){return a*b%m;}
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
    return 1;
}
#include<cstdio>
int calc(int n,long long i=10)
{
    for(;i<=n;i*=100)
        n=n*10+n/i%10;
    return n;
}
main()
{
    freopen("pprime.in","r",stdin);
    freopen("pprime.out","w",stdout);
    int i,j,k,a,b;
    scanf("%d %d",&a,&b);
    for(i=1;i<=10000;i*=10)
    {
        for(j=i;j<i*10;j++)
        {
            k=calc(j);
            if(a<=k && k<=b && isPrime(k))
                printf("%d\n",k);
        }
        for(j=i;j<i*10;j++)
        {
            k=calc(j,1);
            if(a<=k && k<=b && isPrime(k))
                printf("%d\n",k);
        }
    }
    scanf(" ");
}
/*
PROB:pprime
LANG:C++
*/
