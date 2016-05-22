#include<cstdio>
#include<algorithm>
using namespace std;
int pow(long long n,int k,int m)
{
    if(k==0)return 1;
    if(k%2)return pow(n,k-1,m)*n%m;
    n=pow(n,k/2,m);
    return n*n%m;
}
inline int rev(int n,int k)
{
    int i=0;
    while(k--)(i<<=1)+=n&1,n/=2;
    return i;
}
const long long p=1107296257,r=10;
void _ntt(bool f,int& n,int s[])
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
int s[1000000],t[1000000];
char a[250000],b[250000];
main()
{
    int i,j,n1,n2;
    while(scanf("%s %s",a,b)==2)
    {
        for(n1=0;a[n1];n1++);
        for(n2=0;b[n2];n2++);
        
        for(i=0;n1>0;i++,n1-=2)
            sscanf(a+max(0,n1-2),"%02d",s+i);
        n1=i;
        for(i=0;n2>0;i++,n2-=2) 
           	sscanf(b+max(0,n2-2),"%02d",t+i);
        n2=i;
        for(i=2;i<n1+n2 || i<max(n1,n2)*2;i*=2);
        for(;n1<i;n1++)s[n1]=0;
        for(;n2<i;n2++)t[n2]=0;
        
        _ntt(0,n1,s);
        _ntt(0,n2,t);

        mul(n2,t,s);
            
        _ntt(1,n2,t);
        t[n2]=0;
        for(i=0;i<n2;i++)
        {
            t[i+1]+=t[i]/100;
            t[i]%=100;
        }
        if(t[n2])n2++;
        while(n2 && !t[n2-1])n2--;
        printf("%d",t[n2-1]);
        for(i=n2-2;i>=0;i--)
            printf("%d",t[i]);
        puts("");
    }
}
