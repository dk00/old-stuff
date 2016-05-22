#include<cstdio>
const int inf=2000000000;
int o[100][100],c[100][100],u[100],q[99999];
main()
{
    int i,j,k,l,n,m,min,st;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<=n;i++)
            for(j=0;j<=n;j++)
                o[i][j]=inf;
        for(i=0;i<n;i++)
        {
            o[i][i]=0;
            scanf("%d",&m);
            while(m--)
            {
                scanf("%d %d",&j,&k);
                o[i][j-1]=k;
            }
        }
        min=inf;
        for(l=0;l<n;l++)
        {
            for(i=0;i<n;i++)
                for(u[i]=1,j=0;j<n;j++)
                    c[i][j]=o[i][j];
            c[l][l]=0;
            for(i=j=0;i<n;i++)
                if(c[l][i]<inf)
                    q[j++]=i,u[i]=0;
            for(i=0;i<j;i++)
            {
                u[q[i]]=1;
                for(k=0;k<n;k++)
                    if(c[q[i]][k]<inf && c[l][q[i]]+c[q[i]][k]<c[l][k])
                    {
                        c[l][k]=c[l][q[i]]+c[q[i]][k];
                        if(u[k])u[k]--,q[j++]=k;
                    }
            }
            for(i=j=0;i<n;i++)
                j>?=c[l][i];
            if(j<min)
                min=j,st=l;
        }
        if(min<inf)printf("%d %d\n",st+1,min);
        else puts("disjoint");
    }
}
