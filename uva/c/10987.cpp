#include<cstdio>
int c[100][100],u[100][100];
main()
{
    int i,j,k,n,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=m=0;i<n;i++)
            for(j=0;j<i;j++)
            {
                scanf("%d",&c[i][j]),m++;
                c[j][i]=c[i][j],u[i][j]=1;
            }
        printf("Case #%d:\n",C++);
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                {
                    if(i==k || k==j)continue;
                    if(c[i][k]+c[k][j]<c[i][j])
                        goto better;
                    if(c[i][k]+c[k][j]==c[i][j])
                        if(u[i][j])m--,u[i][j]=0;
                }
        printf("%d\n",m);
        for(i=0;i<n;i++)
            for(j=0;j<i;j++)
                if(u[i][j])
                    printf("%d %d %d\n",j+1,i+1,c[i][j]);
        puts("");
        continue;
    better:
        puts("Need better measurements.\n");
    }
}
