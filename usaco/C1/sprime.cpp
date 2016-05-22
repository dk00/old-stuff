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
int go(int num,int d)
{
    if(num && !isPrime(num))return 0;
    if(!d)return printf("%d\n",num);
    if(!num)go(2,d-1);
    for(int i=1+2*!num;i<10;i++,i++)
        go(num*10+i,d-1);
}
main()
{
    freopen("sprime.in","r",stdin);
    freopen("sprime.out","w",stdout);
    int n;
    scanf("%d",&n);
    go(0,n);
}
/*
PROB:sprime
LANG:C++
*/
