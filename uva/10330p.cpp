#include<cstdio>
int s=0,t,p[207],q[207],r[207],c[207][207];
int min(int a,int b){return a<b?a:b;}
int flow()
{
    int i,j,k,f=0;
    while(1){
        for(i=0;i<=t;i++)
            p[i]=i;
        r[s]=200000000;
        q[0]=s;
        for(i=0,j=1;i<j && p[t]==t;i++)
            for(k=0;k<=t;k++)
                if(p[k]==k && c[q[i]][k]>0)
                {
                    p[k]=q[i];
                    r[k]=min(c[q[i]][k],r[q[i]]);
                    q[j++]=k;
                }
        if(p[t]==t)
            break;
        for(k=t;k!=s;k=p[k])
        {
            c[k][p[k]]+=r[t];
            c[p[k]][k]-=r[t];
        }
        f+=r[t];
    }
    return f;
}
main()
{
    int i,j,k,n,m;
    while(scanf("%d",&n)==1 && n)
    {
        t=2*n+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=0;
        for(i=1;i<=n;i++)
            scanf("%d",&c[i][n+i]);
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[i+n][j]+=k;
        }
        scanf("%d %d",&i,&j);
        for(m=0;m<i;m++)
            scanf("%d",&k),c[0][k]=2000000000;
        for(;m<i+j;m++)
            scanf("%d",&k),c[n+k][t]=2000000000;
        printf("%d\n",flow());
    }
}
