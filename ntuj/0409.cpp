#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
const int N=9999,inf=2000000000;
char u[N];
int n,d[N],d1[N];
queue<int> q;
vector<int> to[N],c[N];
int sp()
{
    q.push(0);
    int i,j,k,l;
    while(q.size())
    {
        i=q.front(),q.pop();
        u[i]=0;
        for(l=0;l<to[i].size();l++)
        {
            j=to[i][l];
            k=d[i]+c[i][l];
            if(k<d[j])
            {
                d[j]=k;
                if(!u[j])q.push(j),u[j]=1;
            }
        }
    }
}
int sp0()
{
    int i,j,k,l;
    for(i=0;i<n;i++)
        q.push(i),u[i]=1;
    while(q.size())
    {
        i=q.front(),q.pop();
        u[i]=0;
        for(l=0;l<to[i].size();l++)
        {
            j=to[i][l];
            k=d[i]+c[i][l];
            if(d[j]<k && k<d1[j])
            {
                d1[j]=k;
                if(!u[j])q.push(j),u[j]=1;
            }
            k=d1[i]+c[i][l];
            if(d[j]<k && k<d1[j])
            {
                d1[j]=k;
                if(!u[j])q.push(j),u[j]=1;
            }
        }
    }
}
main()
{
    int i,j,k,m;
    while(~scanf("%d %d",&n,&m))
    {
        for(i=0;i<n;i++)
        {
            to[i].clear(),c[i].clear();
            d[i]=d1[i]=inf;
        }
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            i--,j--;
            to[i].push_back(j);
            c[i].push_back(k);
            to[j].push_back(i);
            c[j].push_back(k);
        }
        d[0]=0;
        sp(),sp0();
        printf("%d\n",d1[n-1]);
    }
}
