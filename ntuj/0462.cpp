#include<queue>
#include<cstdio>
using namespace std;
const int N=100001,inf=N+1;
void sp(int st,int n,int d[])
{
    int i;
    for(i=0;i<n;i++)
        d[i]=inf;
    queue<int> q;
    d[st]=0;
    q.push(st);
    while(q.size())
    {
        i=q.front();
        q.pop();
        if(i-1>=0 && d[i]+1<d[i-1])
            d[i-1]=d[i]+1,q.push(i-1);
        if(i+1<N && d[i]+1<d[i+1])
            d[i+1]=d[i]+1,q.push(i+1);
        if(i*2<N && d[i]+1<d[i*2])
            d[i*2]=d[i]+1,q.push(i*2);
    }
}
int d[N+1];
main()
{
    int n,k;
    while(scanf("%d %d",&n,&k)>0)
    {
        sp(n,N,d);
        printf("%d\n",d[k]);
    }
}
