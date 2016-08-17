#include<cstdio>
#include<algorithm>
struct pa
{
    int x,y;
    bool operator<(pa a)const
    {
        if(x!=a.x)return x<a.x;
        return y>a.y;
    }
}s[20001];
int t[20001],q[20001];
int lis(int s[],int n)
{
    int i,j,k,l,x;
    q[0]=-1;
    for(i=0,l=1;i<n;i++)
    {
        for(j=l-1;j>=0;j--)
            if(s[i]>=q[j])break;
        q[j+1]<?=s[i];
        if(j+1==l)
            q[l++]=s[i];
    }
    return l-1;
}
main()
{
    int i,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d %d",&s[i].x,&s[i].y);
        std::sort(s,s+n);
        for(i=0;i<n;i++)
            t[i]=s[n-i-1].y;
        printf("%d\n",lis(t,n));
    }
}
