#include<cstdio>
#include<algorithm>
using namespace std;
long long s[101][1024];
int m;
void go(long long x,int u,int i,long long t[])
{
    if(i>=m){t[u]+=x;return;}
    if(!(u&(1<<i)) && i+1<m && !(u&(1<<(i+1))))
        go(x,u,i+2,t);
    go(x,u^(1<<i),i+1,t);
}
main()
{
    int i,j,n;
    while(scanf("%d %d",&n,&m)==2)
    {
        if(n<m)swap(n,m);
        for(i=0;i<=n;i++)
            for(j=0;j<(1<<m);j++)
                s[i][j]=0;
        s[0][0]=1;
        for(i=0;i<n;i++)
            for(j=0;j<(1<<m);j++)
                if(s[i][j])
                    go(s[i][j],j,0,s[i+1]);
        printf("%lld\n",s[n][0]);
    }
}
