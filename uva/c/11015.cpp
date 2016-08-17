#include<cstdio>
int c[100][100];
char name[100][20];
main()
{
    int i,j,k,n,m,C=1;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(i=0;i<n;i++)
        {
            scanf("%s",name[i]);
            for(j=0;j<n;j++)
                c[i][j]=200000000;
            c[i][i]=0;
        }
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[i-1][j-1]=c[j-1][i-1]=k;
        }
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    c[i][j]<?=(c[i][k]+c[k][j]);
        for(i=k=0;i<n;i++)
        {
            for(j=1;j<n;j++)
                c[i][0]+=c[i][j];
            if(c[i][0]<c[k][0])k=i;
        }
        printf("Case #%d : %s\n",C++,name[k]);
    }
}
