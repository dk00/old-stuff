#include<cstdio>
int a[6001],b[6001],path[6001],c[25007];
int go(int d,int v,int u)
{
    if(d>1 && path[d-2]==v)
        return -1;
    path[d]=v;
    if(v==u)
        return d+1;
    int tmp;
    for(int i=c[v-1];i<c[v];i++)
        if((tmp=go(d+1,c[i],u))>=0)
            return tmp;
    return -1;
}
main()
{
    int i,j,n,m;
    while(scanf("%d",&n) && n)
    {
        for(i=1;i<=n;i++)
            c[i]=0;
        for(i=1;i<n;i++)
        {
            scanf("%d %d",&a[i],&b[i]);
            c[a[i]]++,c[b[i]]++;
        }
        c[0]=n+1;
        for(i=1;i<=n;i++)
            c[i]+=c[i-1];
        while(i---1)
            c[i]=c[i-1];
        for(i=1;i<n;i++)
        {
            c[c[a[i]]++]=b[i];
            c[c[b[i]]++]=a[i];
        }
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d %d",&i,&j);
            j=go(0,i,j);
            if(j%2)
                printf("The fleas meet at %d.\n",path[j/2]);
            else
                printf("The fleas jump forever between %d and %d.\n",
                path[j/2-1]<?path[j/2],path[j/2-1]>?path[j/2]);
        }
    }
}
