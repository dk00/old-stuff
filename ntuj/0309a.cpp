#include<cstdio>
int q[3][6]={{1,1,1,1,1,-1},{1,-1,-1,1,1,1},{1,1,-1-1,-1,1}};
int n;
main()
{
	int i,j,k,sum;
	while(scanf("%d",&n)==1 && n)
	{
        for(i=0;i<3;i++)
        {
            for(j=0;j<6;j++)
                printf("%d ",q[i][j]);
            puts("");
        }
	}
}
