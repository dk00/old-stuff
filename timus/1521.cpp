#include<cstdio>
int s[131075],l[131075],r[131075];
int build(int st,int ed,int v=1)
{
    if(st>ed)return 0;
    int k=(st+ed)/2;
    s[v]=k;
    r[v]=build(k+1,ed,v*2+1);
    l[v]=build(st,k-1,v*2);
    return 1+l[v]+r[v];
}
int del(int p,int v=1)
{
    if(p<=l[v])
        return l[v]--,del(p,v*2);
    if(p>l[v]+1)
        return r[v]--,del(p-l[v]-1,v*2+1);
    int tmp=s[v];
    if(l[v])
        s[v]=del(l[v]--,v*2);
    else if(r[v])
        r[v]--,s[v]=del(1,v*2+1);
    else s[v]=-1;
    return tmp;
}
main()
{
    int i,n,m;
    scanf("%d %d",&n,&m);
    build(1,n);
    for(i=(m-1)%n--;n>=1;i=(i+m-1)%n--)
        printf("%d ",del(i+1));
    printf("%d\n",del(1));
}
