#include<cstdio>
const int inf=500;
main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                c[i][j]=inf;
        for(i=1;i<=n;i++)d[i]=inf,p[i]=i;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[i][j]=c[j][i]=k;
        }
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                o[i][j]=c[i][j];
        for(k=1;k<=n;k++)
            for(i=1;i<=n;i++)
                for(j=1;j<=n;j++)
                    o[i][j]>?=(o[i][k]>?o[k][j]);
        d[1]=0,p[1]=-1;
        for(k=1;k<n;k++)
        {
            for(i=1;p[i]>=0;i++)
            for(j=i+1;j<=n;j++)
                if(p[i]<0 && d[j]<d[i])i=j;
            sum+=d[i];
            p[i]*=-1;
            for(j=1;j<=n;j++)
                if(p[j]==j || c[i][j]<d[j])
                    d[j]=c[i][j],p[j]=i;
        }
        min=inf;
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(c[i][j]-o[i][j]>0)
                    min<?=c[i][j]-o[i][j];
        printf("%d %d\n",sum,sum+min);
    }
}
