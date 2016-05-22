#include<cstdio>
#include<vector>
using namespace std;
const int N=100001,M=200001;
main()
{
    while(scanf("%d %d",&n,&m)==2){
        for(i=1;i<=n;i++)
            t[i].clear();
        for(i=0;i<m;i++){
            scanf("%d %d",&s[i].a,&s[i].b);
            s[i].u=0;
            t[s[i].a].push_back(i);
            t[s[i].b].push_back(i);
        }
    }
}
