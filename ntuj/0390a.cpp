#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10001,inf=2000000000;
int n,a,b,c[N],s[N],t[2][N],u[N],u0[2][N];
int go(int v)
{
    if(u[v])return s[v];
    for(int i=v+1;i<n;i++)
        if(c[v]+a<=c[i] && c[i]<=c[v]+b)
            if(u[v]++)s[v]>?=c[v]-go(i);
            else s[v]=c[v]-go(i);
    if(!u[v])s[v]=c[v];
    u[v]=1;
    return s[v];
}
int og(int v,int p=0)
{
    if(u0[p][v])return t[p][v];
    for(int i=v+1;i<n;i++)
        if(c[v]+a<=c[i] && c[i]<=c[v]+b)
            if(u0[p][v]++)
            {
                if(p)t[p][v]>?=c[v]-og(i,!p);
                else t[p][v]<?=c[v]-og(i,!p);
            }
            else t[p][v]=c[v]-og(i,!p);
    if(!u0[p][v])t[p][v]=c[v];
    u0[p][v]=1;
    return t[p][v];
}
main()
{
    int i,j,k,l,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&a,&b);
        for(i=0;i<n;i++)
            scanf("%d",c+i),u[i]=u0[0][i]=u0[1][i]=0;
        sort(c,c+n);
        for(i=k=m=0;i<n;i++)
            if(a<=c[i] && c[i]<=b)
                if(m++)k>?=go(i);
                else k=go(i);
        for(i=l=m=0;i<n;i++)
            if(a<=c[i] && c[i]<=b)
                if(m++)l<?=og(i);
                else l=og(i);
        if(abs(k)>abs(l))
            printf("%d\n",k);
        else
            printf("%d\n",l);
    }
}
