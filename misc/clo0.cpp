#include<cstdio>
#include<vector>
using namespace std;
const int N=100001,M=200001;
int un,p[N],q[N];
vector<int> t[N];
struct ed{
    int a,b,u;
}s[M];
int go(int v)
{
    if(q[v]==un)return 0;
    for(int i=p[v]+1;i<t[v].size();i++){
        if((s[t[v][i]].u&1)==0){
            s[t[v][i]].u=un|1;
            p[v]=i;
            return 1;
        }
        if((s[t[v][i]].u&un)==un)
            continue;
        s[t[v][i]].u|=un;
        if(go(s[t[v][i]].a+s[t[v][i]].b-v))
            return 1;
    }
    return 0;
}
main()
{
    int i,j,n,m,sum;
    while(scanf("%d %d",&n,&m)==2){
        for(i=1;i<=n;i++)
            p[i]=-1,t[i].clear();
        for(i=0;i<m;i++){
            scanf("%d %d",&s[i].a,&s[i].b);
            s[i].u=0;
            t[s[i].a].push_back(i);
            t[s[i].b].push_back(i);
        }
        for(un=2,j=1,sum=0;j;un+=2,sum+=j)
            for(i=1,j=0;i<=n;i++)
                if(p[i]<0)j+=go(i);
        if(sum!=n){
            puts("NIE");
            continue;
        }
        for(i=1;i<=n;i++)
            printf("%d\n",s[t[i][p[i]]].a+s[t[i][p[i]]].b-i);
    }
}
