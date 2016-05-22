#include<cmath>
#include<cstdio>
inline int mul(long long a,int b,int x,int m)
{
    if(a*b>x)
        return x+(a*b-x%m+m)%m;
    return a*b;
}
inline int pow(long long n,int k,int m)
{
    int i,a;
    for(i=a=1;i<=k;i*=2,n=n*n%m)
        if(i&k)a=a*n%m;
    return a;
}
inline int pow(int n,int k,int x,int m)
{
    int i;
    long long s=1;
    if(n<=1)k<?=1;
    for(i=0;i<k && s<=x;i++,s*=n);
    if(i>=k && s<=x)return s;
    return x+(pow(n,k,m)-x%m+m)%m;
}
const int M=1000000;
int u[M];
inline int get(int n,int m)
{
    static int a=0;
    a++;
    int i,j,l,y=pow(n,m,0,m),z;
    l=pow(m,0.38);
    for(i=0;i*i<l;i++)
    {
        if(u[y=mul(y,n,0,m)]==a)return i;
        u[y]=a;
    }
    z=pow(n,i,0,m);
    for(j=i*2;u[y=mul(y,z,0,m)]!=a;j+=i);
    for(z=pow(n,m,0,m);(z=mul(z,n,0,m))!=y;j--);
    return j-1;
}
inline int get(int n,int m0,int x,int m)
{
    int a=1,i=1,j,k,y;
    long long l;
    if(n!=1)
        for(i=1,l=n;l<x;l*=n,i++);
    for(j=i+m-m0;i<=j;)
    {
        k=(i+j)/2;
        y=pow(n,k,x,m);
        if(pow(n,k+m0,x,m)==y)
            a=k,j=k-1;
        else
            i=k+1;
    }
    return a;
}
const int N=100000;
int s[N],m[N],x[N];
main()
{
    int i,n,C=1;
    while(scanf("%d",&n)==1 && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        scanf("%d",&m);
        for(i=0;i<n;i++)
        {
            m[i+1]=get(s[i],m[i]);
            x[i+1]=get(s[i],m[i+1],x[i],m[i]);
        }
        s[i]=1;
        while(i--)
            s[i]=pow(s[i],s[i+1],x[i],m[i]);
        printf("%d\n",s[0]);
        //printf("Case #%d: %d\n",C++,s[0]);
    }
}
