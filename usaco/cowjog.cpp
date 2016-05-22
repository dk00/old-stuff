/*
PROB:cowjog
LANG:C++
*/
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
int n,m;
struct ed{int to,c;};
vector<int> to[1001],c[1001];
priority_queue<int> h[1001];
main()
{
    freopen("cowjog.in","r",stdin);
    freopen("cowjog.out","w",stdout);
    int i,j,k,n,m,x;
    scanf("%d %d %d",&n,&m,&x);
    while(m--)
    {
        scanf("%d %d %d",&i,&j,&k);
        to[i-1].push_back(j-1);
        c[i-1].push_back(k);
    }
    h[n-1].push(0);
    while(x--)
    {
        for(i=n-1;i>0;i--)
        {
            if(!h[i].size())continue;
            int tmp=h[i].top();
            for(j=0;j<to[i].size();j++)
                h[to[i][j]].push(tmp-c[i][j]);
            h[i].pop();
        }
        if(h[0].size())
            printf("%d\n",-h[0].top());
        else
            puts("-1");
        if(h[0].size())h[0].pop();
    }
}
