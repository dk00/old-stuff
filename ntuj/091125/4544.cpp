#include<vector>
#include<cstdio>
using namespace std;
const int N=5000;
int n,ub,u[N];
vector<int> c[N];
void go(int d,int v)
{
    if(u[v]>=0){
        if(d-u[v]>ub && d-u[v]!=2)ub=d-u[v];
        return;
    }
    u[v]=d;
    for(int i=0;i<c[v].size();i++)
        go(d+1,c[v][i]);
}
main()
{
    int i,j,m,a,b,T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++){
            u[i]=-1;
            c[i].clear();
        }
        while(m--){
            scanf("%d %d",&a,&b);
            a--,b--;
            c[a].push_back(b);
            c[b].push_back(a);
        }
        ub=0;
        go(0,0);
        printf("%d\n",ub);
    }
}
