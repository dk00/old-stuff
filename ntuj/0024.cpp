#include<cstdio>
int c[500][500];
main()
{
    int i,j,k,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%d",&c[i][j]);
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    c[i][j]>?=(c[i][k]<?c[k][j]);
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d %d",&i,&j);
            printf("%d\n",c[i-1][j-1]);
        }
    }
}
