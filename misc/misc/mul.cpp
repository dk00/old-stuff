#include<cstdio>
#include<algorithm>
using namespace std;
inline int pow(long long n,int k,int m)
{
    unsigned i;
    int a;
    for(a=i=1;i<=k;i*=2,n=(n*n)%m)
        if(k&i)a=(a*n)%m;
    return a;
}
inline int rev(int n,int k)
{
    int i=0;
    while(k--)(i<<=1)+=n&1,n/=2;
    return i;
}
const long long p=1107296257,r=10;
void ntt(bool f,int& n,int s[])
{
    int i,j,k;
    long long x,w;
    for(j=1,k=0;j<n ;j<<=1,k++);
    for(;n<j;n++)s[n]=0;
    for(i=0;i<n;i++)
        if(i<rev(i,k))
            swap(s[i],s[rev(i,k)]);
    for(i=2;i<=n;i*=2)
    {
        w=pow(pow(r,(p-1)/n,p),f?p-1-n/i:n/i,p);
        for(j=0;j<n;j+=i)
            for(k=0,x=1;k<i/2;k++)
            {
                int &a=s[j+k],&b=s[j+k+i/2];
                b=(b*x)%p;
                a=(a*1ll+b)%p;
                b=(a+p+p-b-b)%p;
                x=x*w%p;
            }
    }
    x=pow(n,p-2,p);
    if(f)for(j=0;j<n;j++)
        s[j]=(s[j]*x)%p;
}
void mul(int n,int a[],int b[])
{
    for(int i=0;i<n;i++)
        a[i]=(1ll*a[i]*b[i])%p;
}

void print(int n,int s[])
{
    for(int i=0;i<n;i++)
        printf("%d ",s[i]);
    puts("");
}
const int N=100000;
char a[N],b[N];
int s0[N],s1[N];
main()
{
    int i,j,n;
    while(scanf("%s %s",a,b)>0)
    {
        for(i=0;a[i];i++)
            s0[i]=a[i]-'0';
        reverse(s0,s0+i);
        for(j=0;b[j];j++)
            s1[j]=b[j]-'0';
        reverse(s1,s1+j);
        for(n=1;n<i+j;n*=2);
        for(;i<n;i++)s0[i]=0;
        for(;j<n;j++)s1[j]=0;
        print(n,s0);
        print(n,s1);
        ntt(0,n,s0);
        ntt(0,n,s1);
        mul(n,s0,s1);
        ntt(1,n,s0);
        for(i=n-1;i>=0;i--)
            printf("%d",s0[i]%10);
        puts("");
    }
}
