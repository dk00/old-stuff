#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=2000000000;
struct E
{
    int s,t,c;
    bool operator<(E x)const
    {
        return(s<x.s ||(s==x.s && c<x.c));
    }
}c[1500];
int n,m,u[801],p[801],d[500][800];
void go(int z,int d[800])
{
    int k;
    queue<int> q;
    for(k=0;k<n;k++)d[k]=inf,u[k]=1;
    while(q.size()>0)q.pop();
    q.push(z),d[z]=u[z]=0;
    while(q.size()>0)
    {
        z=q.front(),q.pop();
        u[z]=1;
        for(k=p[z];k<p[z+1];k++)
            if(d[z]+c[k].c<d[c[k].t])
            {
                d[c[k].t]=d[z]+c[k].c;
                if(u[c[k].t])
                    u[c[k].t]=0,q.push(c[k].t);
            }
    }
}
main()
{
    int i,j,k,x,z[500];
    scanf("%d %d %d",&x,&n,&m);
    for(i=0;i<x;i++)
        scanf("%d",&z[i]);
    for(i=0;i<m;i++)
    {
        scanf("%d %d %d",&c[i].s,&c[i].t,&c[i].c);
        c[i].s--,c[i].t--;
        c[i+m]=c[i];
        c[i].s+=c[i].t,
        c[i].t=c[i].s-c[i].t,c[i].s-=c[i].t;
    }
    m*=2;
    std::sort(c,c+m);
    for(i=j=0;i<n;i++)
    {
        while(c[j].s<i)j++;
        p[i]=j;
    }
    p[i]=m;
    for(i=0;i<x;i++)go(z[i]-1,d[i]);
    m=inf;
    for(i=0;i<n;i++)
    {
        for(j=k=0;j<x;j++)
        {
            printf("%d ",d[j][i]);
            k+=d[j][i];
        }
        puts("");
        m<?=k;
    }
    printf("%d\n",m);
    scanf(" ");
}
