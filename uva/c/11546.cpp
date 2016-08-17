#include<map>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> s[50001];
main()
{
    int i,j,k,n,m,C=1;
    map<vector<int>,int> h;
    while(scanf("%d %d",&n,&m)>0 && m+n)
    {
        h.clear();
        for(i=0;i<=n;i++)
            s[i].resize(m),fill(s[i].begin(),s[i].end(),0);
        for(j=0;j<m;j++)
        {
            scanf("%d",&k);
            while(k--)
            {
                scanf("%d",&i);
                s[i][j]=1;
            }
            for(i=1;i<n;i++)
                s[i][j]+=s[i-1][j];
        }
        h[s[n]]=-1;
        for(i=k=0;i<n;i++)
        {
            for(j=1;j<m;j++)
                s[i][j-1]-=s[i][j];
            s[i][m-1]=0;
            if(h.count(s[i]))k>?=i-h[s[i]];
            else h[s[i]]=i;
        }
        printf("Case #%d: %d meter(s)\n",C++,k);
    }
}
