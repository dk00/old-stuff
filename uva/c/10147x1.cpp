#include<cstdio>
#include<cstdlib>
struct pt
{
    int x,y;
    void get()
    {
        scanf("%d %d",&x,&y);
    }
}p[1000];
struct edge
{
    int a,b,c;
}e[600000];
int set[1000],d[1000];
int edgcmp(const void *a,const void *b)
{
    return ((edge *)a)->c-((edge *)b)->c;
}
int find(int v)
{
    if(set[v]==v)
        return v;
    set[v]=find(set[v]);
    return set[v];
}
int uni(int i,int j)
{
    i=find(i);
    j=find(j);
    if(i==j)
        return 0;
    if(d[i]<d[j])
        set[i]=j;
    else if(d[i]>d[j])
        set[j]=i;
    else
    {
        set[i]=j;
        d[j]++;
    }
    return 1;
}
int dis(pt a,pt b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
main()
{
    int i,j,n,m,t,en,root;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            set[i]=i;
            p[i].get();
        }
        scanf("%d",&m);
        root=n;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            if(uni(i-1,j-1)==1)
                root--;
        }
        if(root<=1)
        {
            puts("No new highways need");
            if(t)
                puts("");
            continue;
        }
        for(i=en=0;i<n;i++)
            for(j=0;j<i;j++)
                e[en++]=(edge){i,j,dis(p[i],p[j])};
        qsort(e,en,sizeof(e[0]),edgcmp);
        for(i=0;i<en && root>1;i++)
            if(uni(e[i].a,e[i].b)==1)
            {
                root--;
                printf("%d %d\n",e[i].a+1,e[i].b+1);
            }
        if(t)
            puts("");
    }
}
