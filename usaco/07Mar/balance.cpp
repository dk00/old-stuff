/*
PROG: balance
LANG: C++
ID: s0000151
*/
#include<cstdio>
#include<algorithm>
int p0[2][100010],*p1=p0[0]+50004,*p2=p0[1]+50004;
struct cow
{
    int num,x;
    bool operator<(cow a)const{return x<a.x;}
}s[100001];
main()
{
    freopen("balance.in","r",stdin);
    freopen("balance.out","w",stdout);
    int i,j,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&s[i].num,&s[i].x);
        if(s[i].num==0)s[i].num=-1;
    }
    for(i=-n;i<=n;i++)
        p1[i]=p1[i+1]=p2[i]=p2[i+1]=-1;
    std::sort(s,s+n);
    for(i=1,j=0;i<n;i++)
    {
        s[i].num+=s[i-1].num;
        if(s[i].num==0)
            j>?=s[i].x-s[0].x;
    }
    for(i=0;i<n;i++)
        if(p1[s[i].num]<0)
            p1[s[i].num]=i;
    for(i=n-1;i>=0;i--)
        if(p2[s[i].num]<0)
            p2[s[i].num]=i;
    for(i=-n;i<=n;i++)
        if(p1[i]>=0 && p2[i]>=0 && p1[i]+1<n)
            j>?=(s[p2[i]].x-s[p1[i]+1].x);
    printf("%d\n",j);
}
