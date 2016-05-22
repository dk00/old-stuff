#include<cstdio>
struct Q
{
    int v,d;
}q[10000];
int n,d[100],p[100],c1[100][100],c2[100][100];
int flow(int num,int cap)
{
    int i,j,k,nv,nd,cost,sum=0;
    while(num>0)
    {
        for(i=0;i<n;i++)p[i]=i;
        q[0]=(Q){0,0},d[0]=0;
        for(i=0,j=1;i<j;i++)
        {
            nv=q[i].v,nd=q[i].d;
            if(d[nv]<nd)continue;
            for(k=0;k<n;k++)
                if(c1[nv][k] && (nd+c2[nv][k]<d[k] || p[k]==k))
                {
                    d[k]=nd+c2[nv][k];
                    p[k]=nv,q[j++]=(Q){k,d[k]};
                }
        }
        if(p[n-1]==n-1)break;
        for(i=n-1,cost=0;i;i=p[i])
        {
            cost+=c2[p[i]][i];
            c2[p[i]][i]=-c2[p[i]][i];
            c2[i][p[i]]=-c2[i][p[i]];
            c1[p[i]][i]--,c1[i][p[i]]++;
        }
        if(num>=cap)sum+=cap*cost;
        else sum+=num*cost;
        num-=cap;
    }
    if(num>0)
        return -1;
    return sum;
}
main()
{
    int i,j,k,m;
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c1[i][j]=c2[i][j]=0;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c1[i-1][j-1]=c1[j-1][i-1]=1;
            c2[i-1][j-1]=c2[j-1][i-1]=k;
        }
        scanf("%d %d",&i,&j);
        k=flow(i,j);
        if(k<0)puts("Impossible.");
        else printf("%d\n",k);
    }
}
