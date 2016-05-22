#include<cstdio>
#include<algorithm>
using namespace std;
const int V=1000;
int p[V],d[V];
int find(int v)
{
    if(p[v]==v)return v;
    return p[v]=find(p[v]);
}
void uni(int a,int b)
{
    a=find(a),b=find(b);
    if(d[a]<d[b])p[a]=b;
    else p[b]=a;
    if(d[a]==d[b])d[a]++;
}
void init(int n)
{
    while(n--)p[n]=n,d[n]=0;
}
struct pt
{
    int x,y;
    int operator+(pt a){return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);}
}pos[V];
struct ed
{
    int s,t,c;
    bool operator<(ed x)const{return c<x.c;}
}s[V*V];
int n,m;
int cnt;
void printedge(int a,int b,int c)
{
    if(!c)return;
    printf("%d %d\n",a+1,b+1);
    cnt++;
}
int kuskal()
{
    std::sort(s,s+m);
    init(n);
    int i,sum;
    for(i=0;i<m;i++)
    {
        if(find(s[i].s)==find(s[i].t))continue;
        uni(s[i].s,s[i].t);
        sum+=s[i].c;
        printedge(s[i].s,s[i].t,s[i].c);
    }
    return sum;
}
int c[V][V];
int prim()
{
    const int inf=2147483647;
    int i,j,sum=0;
    for(i=0;i<n;i++)
        if(c[0][i]<inf)
            d[i]=c[0][i],p[i]=0;
        else d[i]=inf,p[i]=i;
    p[0]=-1;
    while(1)
    {
        for(i=0;i<n;i++)
            if(d[i]>=0 && d[i]<inf)break;
        if(i>=n)break;
        for(j=i+1;j<n;j++)
            if(d[j]>=0 && d[j]<d[i])i=j;
        printedge(p[i],i,c[p[i]][i]);
        for(j=0;j<n;j++)
            if(c[i][j]<d[j])
                d[j]=c[i][j],p[j]=i;
        sum+=d[i];
        d[i]=-1;
    }
    return sum;
}
main()
{
    int i,j,T;
    scanf("%d",&T);
    while(T--)
    {
        cnt=0;
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d %d",&pos[i].x,&pos[i].y);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=pos[i]+pos[j];
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i-1][j-1]=c[j-1][i-1]=0;
        }
        for(i=m=0;i<n;i++)
            for(j=0;j<i;j++)
                s[m++]=(ed){i,j,c[i][j]};
        prim();
        if(!cnt)puts("No new highways need");
        if(T)puts("");
    }
}
