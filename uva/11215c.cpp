#include<cstdio>
#include<algorithm>
using namespace std;
int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
struct ra
{
    int a,b;
    void reduce()
    {
        int d=gcd(a,b);
        a/=d,b/=d;
    }
    bool operator<(ra x)const{return a*x.b<x.a*b;}
    ra operator+(ra x)const
    {
        int d=gcd(b,x.b);
        ra tmp={x.b/d*a+b/d*x.a,b/d*x.b};
        tmp.reduce();
        return tmp;
    }
    ra operator-(ra x)const
    {
        int d=gcd(b,x.b);
        ra tmp={x.b/d*a-b/d*x.a,b/d*x.b};
        tmp.reduce();
        return tmp;
    }
    ra operator*(ra x)const
    {
        ra tmp={a*x.a,b*x.b};
        tmp.reduce();
        return tmp;
    }
    ra operator/(ra x)const
    {
        ra tmp={a*x.b,b*x.a};
        tmp.reduce();
        return tmp;
    }
};
int n,tn[7],u[64],mem;
ra *s[64],tmp[7][300000];
void reduce(ra s[],int &n)
{
    int j,k;
    sort(s,s+n);
    for(j=k=1;j<n;j++)
        if(s[j]<s[k-1] || s[k-1]<s[j])
            s[k++]=s[j];
    n=k;
}
void go(int v,int d=0)
{
    if(s[v])return;
    int i,j,k;
    for(i=1,tn[d]=0;i<(1<<n);i++)
        if((v&i)==i &&(v^i))
        {
            go(i,d+1),go(v^i,d+1);
            for(j=0;j<u[i^v];j++)
                for(k=0;k<u[i];k++)
                {
                    tmp[d][tn[d]++]=s[i^v][j]+s[i][k];
                    if(tn[d]>=290000)
                        reduce(tmp[d],tn[d]);
                    tmp[d][tn[d]++]=s[i^v][j]-s[i][k];
                    tmp[d][tn[d]++]=s[i^v][j]*s[i][k];
                    if(s[i][k].a)tmp[d][tn[d]++]=s[i^v][j]/s[i][k];
                    
                }
        }
    reduce(tmp[d],tn[d]);
    k=tn[d];
    s[v]=new ra[k],u[v]=k;
    mem+=k;
    if(mem>20971520)mem/=0;
    for(j=0;j<k;j++)
        s[v][j]=tmp[d][j];
}
main()
{
    int i,C=1,num[7];
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",num+i);
        for(i=0;i<n;i++)
        {
            s[1<<i]=new ra[1];
            s[1<<i][0]=(ra){num[i],1};
            u[1<<i]=1;
        }
        mem=0;
        go((1<<n)-1);
        printf("Case %d: %d\n",C++,u[(1<<n)-1],mem);
        for(i=0;i<64;i++)
        {
            u[i]=0;
            if(s[i])delete s[i];
            s[i]=0;
        }
    }
}
