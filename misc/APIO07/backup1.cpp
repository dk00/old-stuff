#include<cstdio>
const int inf=2100000000;
int s[100000];
int go(int st,int ed,int m)
{
    int i,j,mid=(st+ed)/2,min=inf,last,tmp;
    if(m==0)return 0;
    if(m==1)
    {
        for(;st<=ed;st++)
            min<?=s[st];
        return min;
    }
    if((ed-st+2)/2<m || st>ed)return inf/2;
    for(j=0;j<2;j++,mid++)
    {
        last=inf;
        for(i=m/2;i>=0;i--)
        {
            tmp=go(st,mid-1,i)+go(mid+1,ed,m-i);
            if(tmp>last)break;
            last=tmp;
            min<?=tmp;
        }
        last=inf;
        for(i=m/2;i<=m;i++)
        {
            tmp=go(st,mid-1,i)+go(mid+1,ed,m-i);
            if(tmp>last)break;
            min<?=tmp;
        }
    }
    return min;
}
main()
{
    int i,n,m;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        for(i=0,n--;i<n;i++)
            s[i]=s[i+1]-s[i];
        printf("%d\n",go(0,n-1,m));
    }
}
