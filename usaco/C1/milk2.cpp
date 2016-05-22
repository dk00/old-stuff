/*
LANG:C++
TASK:milk2
*/
#include<cstdio>
#include<algorithm>
struct V
{
    int t,x;
    bool operator<(V a)const
    {
        if(t!=a.t)return t<a.t;
        return x<a.x;
    }
}s[10005];
main()
{
    freopen("milk2.in","r",stdin);
    freopen("milk2.out","w",stdout);
    int i,j,k,n,m1,m2;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&s[i].t,&s[i+n].t);
        s[i+n].x=1;
    }
    std::sort(s,s+(n*=2));
    k=s[0].t;
    for(i=j=0,m1=m2=0;i<n;i++)
    {
        if(j)m1>?=(s[i].t-k);
        else m2>?=(s[i].t-k);
        if(j==s[i].x)k=s[i].t;
        if(s[i].x)j--;
        else j++;
    }
    printf("%d %d\n",m1,m2);
    scanf(" ");
}
