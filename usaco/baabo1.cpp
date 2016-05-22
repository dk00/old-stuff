/*
LANG:C++
PROB:baabo
*/
#include<cstdio>
#include<cstdlib>
const long long inf=10000000000000ll,N=1005;
int a[N],b[N],p1[N][N],p2[N][N];
long long s1[N],s2[N],s[N][N];
long long cost(int a1,int b1,int a2,int b2)
{
    return (s1[a2]-s1[a1])*(s1[a2]-s1[a1])
    +(s2[b2]-s2[b1])*(s2[b2]-s2[b1]);
}
int count;
void go(int x,int y)
{
    s[x][y]=-inf;
    int i,j,p,q;
    p=p1[x-1][y]<?p1[x][y-1];
    q=p2[x-1][y]<?p2[x][y-1];
    long long tmp,sub,last;
    j=y-1;
    for(i=p;i<x;i++,count++)
    {
        tmp=s[i][j]-cost(i,j,x-1,y-1);
        if(tmp>s[x][y])
            s[x][y]=tmp,p1[x][y]=i,p2[x][y]=j,sub=-inf;
        else if(tmp>sub)
            sub=tmp;
    }
    i=x-1;
    for(j=q;j<y;j++,count++)
    {
        tmp=s[i][j]-cost(i,j,x-1,y-1);
        if(tmp>s[x][y])
            s[x][y]=tmp,p1[x][y]=i,p2[x][y]=j;
    }
    s[x][y]+=a[x]*b[y];
}
main()
{
    freopen("baabo.in","r",stdin);
    freopen("baabo.out","w",stdout);
    int i,j,k,n,st,ed,last;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        s1[i]=s1[i-1]+a[i];
        s[i][0]=-inf;
    }
    for(i=1;i<=n;i++)
    {
        scanf("%d",b+i);
        s2[i]=s2[i-1]+b[i];
        s[0][i]=-inf;
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            s[i][j]=-inf;
    for(k=32;;k*=2)
    {
        for(i=1;i<=n;i++)
        {
            st=(i-k)>?1;
            ed=(i+k)<?n;
            for(j=st;j<=ed;j++)
                go(i,j);
        }
        go(n+1,n+1);
        if(s[n+1][n+1]==last)break;
        last=s[n+1][n+1];
    }
    //printf("%d ",k);
    printf("%lld\n",s[n+1][n+1]);
}
