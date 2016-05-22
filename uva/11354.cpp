#include<cstdio>
#include<algorithm>
struct ed
{
    int x,y,c;
    bool operator<(ed a)const{return c<a.c;}
}s[100000];
int p[50001],d[50001],c[50001];
int find(int v)
{
    while(v!=p[v])v=p[v];
    return v;
}
void uni(int a,int b,int x)
{
    a=find(a),b=find(b);
    if(a==b)return;
    if(d[a]<d[b])
        p[a]=b,c[a]=x;
    else
        p[b]=a,c[b]=x;
    if(a==b)d[a]++;
}
main()
{
    int i,j,k,n,m,min,C=0;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<=n;i++)
            p[i]=i,d[i]=0;
        for(i=0;i<m;i++)
            scanf("%d %d %d",&s[i].x,&s[i].y,&s[i].c);
        std::sort(s,s+m);
        for(i=0;i<m;i++)
            uni(s[i].x,s[i].y,s[i].c);
        for(i=0;i<=n;i++)
            d[i]=-2;
        scanf("%d",&m);
        if(C++)puts("");
        while(m--)
        {
            scanf("%d %d",&i,&j);
            for(k=i;p[k]!=k;k=p[k])
                d[k]=m;
            d[k]=m;
            for(min=0;d[j]!=m;j=p[j])
                min>?=c[j];
            for(;i!=j;i=p[i])
                min>?=c[i];
            printf("%d\n",min);
        }
    }
}
