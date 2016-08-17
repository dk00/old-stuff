#include<cstdio>
int c[30][30],inf=1000;
main()
{
    int i,j,k,n,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=inf;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i][j]=c[j][i]=1;
        }
        for(i=0;i<n;i++)c[i][i]=0;
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    if(i!=k && k!=j && c[i][k]+c[k][j]<c[i][j])
                        c[i][j]=c[i][k]+c[k][j];
        for(i=k=0;i<n;i++)
            for(j=0;j<n;j++)
                k>?=c[i][j];
        printf("Case #%d:\n%d\n\n",C++,k);
    }
}
