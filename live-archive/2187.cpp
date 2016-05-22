#include<cstdio>
int p[30001],d[30001];
int find(int v)
{
    if(v==p[v])return v;
    return p[v]=find(p[v]);
}
void uni(int v,int u)
{
    v=find(v),u=find(u);
    if(d[v]<d[u])p[v]=u;
    else p[u]=v;
    if(d[v]==d[u])d[v]++;
}
main()
{
    int i,j,k,n,m;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(i=0;i<n;i++)p[i]=i,d[i]=0;
        while(m--)
        {
            scanf("%d",&k);
            k--,scanf("%d",&i);
            while(k--)
            {
                scanf("%d",&j);
                uni(i,j);
            }
        }
        for(i=j=0;i<n;i++)
            if(find(i)==find(0))j++;
        printf("%d\n",j);
    }
}
