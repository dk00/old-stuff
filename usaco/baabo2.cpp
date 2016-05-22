/*
LANG:C++
PROB:baabo
*/
#include<cstdio>
#include<cstdlib>
const long long inf=10000000000000ll,N=1005;
struct next
{
    int n;
    int to[N],p[N];
    long long v[N];
    void set(int m)
    {
        for(int i=0;i<=m+1;i++)
            to[i]=m+5;
        n=0;
    }
    void add(int pos,int val)
    {
        while(n && val>v[n-1])
        {
            to[p[--n]]=pos;
            if(to[p[n]]<=p[n])
            {
                putchar('!');
                scanf("%d");
            }
        }
        v[n]=val,p[n++]=pos;
    }
    int go(int i){return to[i];}
}q1[N],q2[N];

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
    long long tmp,last;
    j=y-1;
    if(x==9 && y==9)
    {
        x=9;
    }
    while(q1[j].go(p)<x)
        p=q1[j].go(p);
    for(i=p;i<x;i++,count++)
    {
        tmp=s[i][j]-cost(i,j,x-1,y-1);
        if(tmp>s[x][y])
            s[x][y]=tmp,p1[x][y]=i,p2[x][y]=j;
    }
    i=x-1;
    while(q2[i].go(q)<y)
        q=q2[i].go(q);
    for(j=q;j<y;j++,count++)
    {
        tmp=s[i][j]-cost(i,j,x-1,y-1);
        if(tmp>s[x][y])
            s[x][y]=tmp,p1[x][y]=i,p2[x][y]=j;
    }
    s[x][y]+=a[x]*b[y];
    q1[y].add(x,s[x][y]);
    q2[x].add(y,s[x][y]);
}
main()
{
    //freopen("b1.in","r",stdin);
    //freopen("baabo.out","w",stdout);
    int i,j,n;
    scanf("%d",&n);
    for(i=0;i<=n;i++)
        q1[i].set(n+1),q2[i].set(n+1);
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
            go(i,j);
    p1[n][n+1]=p1[n+1][n]=p1[n][n];
    p2[n][n+1]=p2[n+1][n]=p2[n][n];
    go(n+1,n+1);
    printf("%lld\n",s[n+1][n+1]);
    printf("%lf\n",count/1.0/n/n);
}
