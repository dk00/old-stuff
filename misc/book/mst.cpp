#include<algorithm>
using namespace std;
const int V=1000;
int n,m,p[V],d[V],c[V][V];
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
    }
    return sum;
}
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
        for(j=0;j<n;j++)
            if(c[i][j]<d[j])
                d[j]=c[i][j],p[j]=i;
        sum+=d[i];
        d[i]=-1;
    }
    return sum;
}
