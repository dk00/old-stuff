#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
const double inf=10e100;
struct ed{int t,v,l;};
struct pt{int v,sp;};

double d[200][501];
pt p[200][501];
char u[200][501];
void print(int i,int j)
{
    if(i)print(p[i][j].v,p[i][j].sp);
    printf("%d ",i);
}
main()
{
    vector<ed> c[200];
    queue<pt> q;
    pt x;
    int i,j,k,l,n,m,t;
    while(scanf("%d %d %d",&n,&m,&t)==3)
    {
        for(i=0;i<n;i++)
        {
            c[i].clear();
            for(j=0;j<=500;j++)
                d[i][j]=inf,u[i][j]=1;
        }
        while(m--)
        {
            scanf("%d %d %d %d",&i,&j,&k,&l);
            c[i].push_back((ed){j,k,l});
        }
        q.push((pt){0,70});
        d[0][70]=0;
        while(!q.empty())
        {
            x=q.front(),q.pop();
            u[x.v][x.sp]=1;
            for(i=0;i<c[x.v].size();i++)
            {
                j=c[x.v][i].t;
                k=c[x.v][i].v?c[x.v][i].v:x.sp;
                if(d[x.v][x.sp]+c[x.v][i].l*1.0/k<d[j][k])
                {
                    d[j][k]=d[x.v][x.sp]+c[x.v][i].l*1.0/k;
                    p[j][k]=x;
                    if(u[j][k])
                        q.push((pt){j,k}),u[j][k]=0;
                }
            }
        }
        for(i=j=0;i<=500;i++)
            if(d[t][i]<d[t][j])j=i;
        print(p[t][j].v,p[t][j].sp);
        printf("%d\n",t);
    }
}
