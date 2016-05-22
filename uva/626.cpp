#include<stdio.h>
int c[100][100];
main()
{
    int i,j,k,n,total;
    while(scanf("%d",&n)!=EOF)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%d",&c[i][j]);
        total=0;
        for(i=0;i<n;i++)
        {
            for(j=0;j<i;j++)
            {
                if(c[i][j]==0)
                    continue;
                for(k=0;k<j;k++)
                    if(c[j][k]==1)
                    {
                        printf("%d %d %d\n",i+1,j+1,k+1);
                        total++;
                    }
            }
            for(j=i+1;j<n;j++)
            {
                if(c[i][j]==0)
                    continue;
                for(k=j+1;k<n;k++)
                    if(c[j][k]==1)
                    {
                        printf("%d %d %d\n",i+1,j+1,k+1);
                        total++;
                    }
            }
        }
        printf("total:%d\n\n",total);
    }
}
