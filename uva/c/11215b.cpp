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
        d=gcd(a,b);
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
    ra operator*(ra x)const
    {
        ra tmp={a*x.b,b*x.a};
        tmp.reduce();
        return tmp;
    }
};
int bit(int n)
{
    if(n)return n%2+bit(n/2);
    return 0;
}
int tn[7],t1[7],t2[7];
q tmp[7][Maxn],tmp1[7][Maxn],tmp2[7][Maxn];
void add(int ch,int n,int d=0,int i=0)
{
    if(n==1)
    {
        for(i=0;(1<<i)!=ch;i++);
        tmp2[d-1][t2[d-1]++]=(q){num[i],1};
        return;
    }
    for(;i<=n-i;i++)
        for(j=0;j<cn[i];j++)
        {
            if((ch&c[i][j])!=c[i][j])continue;
            add(ch^c[i][j],n-i,d+1,i);
            copy_n(tmp2[d],t2[d],tmp1[d]);
            t1[d]=t2[d],t2[d]=0;
            sub(c[i][j],n-1,d+1);
            mul(c[i][j],n-i,d+1);
            div(c[i][j],n-i,d+1);
        }
    for(i=tn=0;i<t1[d];i++)
        for(j=0;j<t2[d];j++)
            tmp[d][tn++]=tmp1[d][i]+tmp2[d][j];
    sort(tmp[d],tn[d]);
    for(i=j=1;i<n;i++)
        if(tmp[d][i]!=tmp[d][j-1])
            tmp[d][j++]=tmp[d][i];
    copy_n(tmp[d],tn[d],tmp2[d-1]+t2[d-1]);
    t2[d-1]+=tn[d];
}
main()
{
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)cn[i]=0;
        for(i=(1<<n)-1;i>0;i--)
            c[bit(i)][cn[bit(i)]++]=i;
        for(i=0;i<n;i++)
            scanf("%d",num+i);
        add((1<<n)-1,n);
        sub((1<<n)-1,n);
        mul((1<<n)-1,n);
        div((1<<n)-1,n);
    }
}
