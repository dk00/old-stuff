#include<cstdio>
#include<algorithm>
using namespace std;
struct pt
{
    int x,y,u;
    bool operator<(pt a)const
    {
        if(x!=a.x)return x<a.x;
        return y<a.y;
    }
}s[99999];
int s1[99999],s2[99999];
long long go(int st,int ed)
{
    if(st>=ed)return 0;
    int i,j,k,m=(st+ed)/2;
    long long sum=go(st,m)+go(m+1,ed);
    for(i=k=st,j=m+1;k<=ed;k++)
        if(j>ed ||(i<=m && s1[i]<=s1[j]))
            s2[k]=s1[i++],sum+=ed-j+1;
        else
            s2[k]=s1[j++];
    for(i=st;i<=ed;i++)
        s1[i]=s2[i];
    return sum;
}
main()
{
    int i,j,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d %d",&s[i].x,&s[i].y),s[i].y*=-1;
        sort(s,s+n);
        for(i=0;i<n;i++)
            s1[i]=s[i].y;
        printf("%lld\n",go(0,n-1));
    }
}
