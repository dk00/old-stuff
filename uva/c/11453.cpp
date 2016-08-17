#include<map>
#include<vector>
#include<cstdio>
using namespace std;
const int inf=2147483647;
void sp(int st,int d[])
{
    for(i=0;i<n;i++)
        u[i]=1,d[i]=inf;
    q[0]=st,u[st]=0,d[0]=24;
    for(i=0,j=1;i<j;i++)
    {
        u[q[i]]=1;
        for(k=0;k<c[i].size();k++)
            if(d[q[i]]+c[i][k].c<d[c[i][k].t])
            {
                d[c[i][k].t]=d[q[i]]+c[i][k].c;
                if(u[c[i][k].t])
                    u[q[j++]=c[i][k].t]=0;
            }
    }
    for(i=0;i<n;i++)
        d[i]/=25;
}
main()
{
    while(scanf("%d",&n)==1)
    {
        map<string,int> h;
        for(i=0;i<n;i++)
        {
            scanf("%s",tmp0);
            h[tmp0]=i;
        }
        scanf("%d",&m);
        while(m--)
        {
            scanf("%s %s %d",tmp0,tmp1,&k);
            i=h[tmp0],j=h[tmp1];
            c[i].push_back({ed}(j,k));
            c[j].push_back({ed}(i,k));
        }
        for(i=0;i<n;i++)
            sp(i,d[i]);
        scanf("%d",&T);
        while(T--)
        {
        }
    }
}//420
