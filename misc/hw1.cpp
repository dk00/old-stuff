#include<cstdio>
int p[51][51];
main()
{
    int i,j,n,m;
    char tmp[1000];
    p[0][0]=1;
    for(i=1;i<=50;i++)
    {
        p[i][0]=1;
        for(j=1;j<=50;j++)
            p[i][j]=p[i-1][j-1]+p[i-1][j];
    }
    while(1)
    {
        printf("Please Enter (n,m): ");
        gets(tmp);
        if(sscanf(tmp,"%d %d",&n,&m)==2)
            printf("%d\n",p[n][m]);
        else break;
    }
}
