/*
TASK:icow
LANG:C++
*/
#include<cstdio>
#include<algorithm>
struct pa
{
    int a,b;
    bool operator<(pa x)const
    {
        if(a!=x.a)return a>x.a;
        return b<x.b;
    }
}s[1001];
main()
{
    freopen("icow.in","r",stdin);
    freopen("icow.out","w",stdout);
    int i,j,n,t;
    scanf("%d %d",&n,&t);
    for(i=0;i<n;i++)
    {
        scanf("%d",&s[i].a);
        s[i].b=i+1;
    }
    std::sort(s,s+n);
    while(t--)
    {
        printf("%d\n",s[0].b);
        for(i=1;i<n;i++)s[i].a+=s[0].a/(n-1);
        if(n==1)continue;
        for(i=1;i<=s[0].a%(n-1);i++)
            s[i].a++;
        s[n]=s[0];
        s[n].a=0;
        for(i=0;i<n;i++)
            s[i]=s[i+1];
    }
}
