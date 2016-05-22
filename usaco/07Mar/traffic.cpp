/*
PROG: traffic
LANG: C++
ID: s0000151
*/
#include<cstdio>
#include<algorithm>
struct E
{
    int s,t;
    bool operator<(E a)const{return s<a.s;}
}c[50001];
int s[5001],t[5001];
main()
{
    freopen("traffic.in","r",stdin);
    freopen("traffic.out","w",stdout);
    int i,j,n,m;
    scanf("%d %d",&n,&m);
    for(i=0;i<m;i++)
        scanf("%d %d",&c[i].s,&c[i].t),
        c[i].s--,c[i].t--;
    std::sort(c,c+m);
    for(i=0;i<n;i++)s[i]=t[i]=0;
    for(i=0;i<m;i++)
    {
        if(s[c[i].s]==0)s[c[i].s]=1;
        s[c[i].t]+=s[c[i].s];
    }
    t[n-1]=1;
    for(i=m-1;i>=0;i--)
        t[c[i].s]+=t[c[i].t];
    for(i=j=0;i<m;i++)
        j>?=s[c[i].s]*t[c[i].t];
    printf("%d\n",j);
}
