#include<cstdio>
const int inf=200000000;
int c[100][100],o[100][100],p[100][100];
void print(int s,int t)
{
    if(p[s][t]>=0)
    {
        print(s,p[s][t]);
        printf(" %d",p[s][t]+1);
        print(p[s][t],t);
    }
}
main()
{
    int i,j,k,n,m,min;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=inf;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            if(c[i-1][j-1]>k)c[i-1][j-1]=k;
            if(c[j-1][i-1]>k)c[j-1][i-1]=k;
            p[i-1][j-1]=p[j-1][i-1]=-1;
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                o[i][j]=c[i][j];
        min=inf;
        for(k=0;k<n-1;k++)
        {
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    if(c[i][k]+c[k][j]<c[i][j])
                        c[i][j]=c[i][k]+c[p[i][j]=k][j];
            for(i=0;i<=k;i++)
                for(j=i+1;j<=k;j++)
                    if(min>o[k+1][i]+c[i][j]+o[j][k+1])
                        min=(o[k+1][i]+c[i][j]+o[j][k+1]);
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=o[i][j];
        for(k=0;k+1<n && min>=0;k++)
        {
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    if(c[i][k]+c[k][j]<c[i][j])
                        c[i][j]=c[i][k]+c[p[i][j]=k][j];
            for(i=0;i<=k && min>=0;i++)
                for(j=i+1;j<=k && min>=0;j++)
                    if(o[k+1][i]+c[i][j]+o[j][k+1]<inf &&
                    o[k+1][i]+c[i][j]+o[j][k+1]==min)
                    {
                        printf("%d %d",k+2,i+1);
                        print(i,j),min=-1;
                        printf(" %d\n",j+1);
                    }
        }
        
        if(min>=inf)
            puts("No solution.");
    }
}
