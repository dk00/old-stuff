#include<cstdio>
const int inf=2000000000,r[][3]={{1,1,1},{1,1,-1},{1,-1,1},{1,-1,-1}};
main()
{
    int i,j,k,n,s[3],min[4],max[4],T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<4;i++)
            min[i]=inf,max[i]=-inf;
        scanf("%d",&n);
        while(n--)
        {
            for(j=0;j<3;j++)
                scanf("%d",&s[j]);
            for(i=0;i<4;i++)
            {
                for(j=k=0;j<3;j++)
                    k+=r[i][j]*s[j];
                min[i]<?=k,max[i]>?=k;
            }
        }
        for(i=k=0;i<4;i++)
            k>?=(max[i]-min[i]);
        printf("Case #%d: %d\n",C++,k);
    }
}
