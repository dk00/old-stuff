#include<stdio.h>
struct pt
{
    double x,y;
    void get()
    {
        scanf("%lf %lf",&x,&y);
    }
}gfpos[100],holpos[100];
int t,pre[202],cap[202][202];
double dis(pt a,pt b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
int findpath(int v){
    if(v==t)return 1;
    for(int i=1;i<=t;i++)
        if(pre[i]==-1 && cap[v][i]>0)
        {
            cap[v][i]--;
            pre[i]=v;
            if(findpath(i)==1)
            {
                cap[i][v]++;
                return 1;
            }
            cap[v][i]++;
        }
    return 0;
}
int flow()
{
    int i,f=0;;
    while(1)
    {
        for(i=1;i<=t;i++)
            pre[i]=-1;
        if(findpath(0)==0)
            return f;
        f++;
    }
}
main()
{
    int i,j,n,m,s,v,maxdis;
    while(1)
    {
        if(scanf("%d %d %d %d",&n,&m,&s,&v)==EOF)
            break;
        maxdis=s*s*v*v;
        t=n+m+1;
        for(i=0;i<n;i++)
            gfpos[i].get();
        for(i=0;i<m;i++)
            holpos[i].get();
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                cap[i][j]=0;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                if(maxdis-dis(gfpos[i],holpos[j])>1e-7)
                    cap[i+1][n+1+j]=1;
        for(i=1;i<=n;i++)
            cap[0][i]=1;
        for(j=0;j<m;j++)
            cap[n+1+j][t]=1;
        printf("%d\n",n-flow());
    }
}
