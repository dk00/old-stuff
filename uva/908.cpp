#include<cstdio>
#include<algorithm>
struct pair1
{
    int a,b,w;
    bool operator<(pair1 x)const{return w<x.w;}
}s[1000012];
int n,c[1000010],d[1000010];
int find(int v)
{
    if(c[v]==v)return v;
    c[v]=find(c[v]);
    return c[v];
}
void uni(int v,int u)
{
    if(d[v]>d[u])
        c[u]=v;
    else if(d[v]<d[u])
        c[v]=u;
    else
    {
        if(d[v]==d[u])
            d[v]++;
        c[u]=v;
    }
}
main()
{
    int i,j,k,sum,C=1;
    while(scanf("%d",&n)==1)
    {
        if(C)C=0;
        else puts("");
        n--;
        for(i=k=0;i<n;i++)
        {
            scanf("%d %d %d",&s[i].a,&s[i].b,&s[i].w);
            k+=s[i].w;
        }
        printf("%d\n",k);
        scanf("%d",&j);
        for(i=n,n+=j;i<n;i++)
            scanf("%d %d %d",&s[i].a,&s[i].b,&s[i].w);
        scanf("%d",&j);
        while(j--)
            scanf("%d %d %d",&i,&i,&i);
        std::sort(s,s+n);
        for(i=1;i<=n;i++)
            c[i]=i,d[i]=0;
        for(k=sum=0;k<n;k++)
        {
            i=find(s[k].a);
            j=find(s[k].b);
            if(i!=j)
            {
                uni(i,j);
                sum+=s[k].w;
            }
        }
        printf("%d\n",sum);
    }
}
