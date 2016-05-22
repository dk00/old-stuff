#include<cstdio>
const int N=30001;
int p[N],d[N];
int find(int v)
{
    if(v==p[v])return v;
    return p[v]=find(p[v]);
}
void uni(int a,int b)
{
    a=find(a),b=find(b);
    if(d[a]<d[b])p[a]=b;
    else p[b]=a;
    if(d[a]==d[b])d[a]++;
}
main()
{
    int i,j,k,n,m;
    while(scanf("%d %d",&n,&m)>0 && n+m)
    {
        for(i=0;i<n;i++)p[i]=i,d[i]=0;
        while(m--)
        {
            scanf("%d",&k);
            for(i=-1;k--;i=j)
            {
                scanf("%d",&j);
                if(i>=0)uni(i,j);
            }
        }
        for(i=j=0;i<n;i++)
            if(find(i)==find(0))j++;
        printf("%d\n",j);
    }
}
