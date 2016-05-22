/*
PROB:acquire
LANG:C++
*/
#include<cstdio>
#include<algorithm>
using namespace std;
const long long inf=(1ll<<62);
long long c[50001];
struct pt
{
    int x,y;
    bool operator<(pt a)const
    {
        if(x!=a.x)return x<a.x;
        return y<a.y;
    }
}s[50001];
main()
{
    freopen("acquire.in","r",stdin);
    freopen("acquire.out","w",stdout);
    int i,j,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d %d",&s[i].x,&s[i].y);
    sort(s,s+n);
    for(i=j=0;i<n;i++)
    {
        c[i]=inf;
        if(s[i].y<s[j].y)j++;
        s[j]=s[i];
    }
    n=j+1;
    if(n<=6000)
        for(i=0;i<n;i++)
            for(j=0;j<=i;j++)
                c[i]<?=(j?c[j-1]:0)+s[j].y*1ll*s[i].x;
    else
        for(i=0,j=1;i<n;i++)
        {
            long long tmp,last=inf;
            for(j--;j<=i;j++)
            {
                tmp=(j?c[j-1]:0)+s[j].y*1ll*s[i].x;
                if(tmp>last)break;
                last=tmp;
            }
            c[i]<?=last;
        }
    printf("%lld\n",c[n-1]);
}
