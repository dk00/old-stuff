#include<cstdio>
int s[100][100],u[100][100];
int go(int i,int j)
{
    if(u[i][j])
        return s[i][j];
    u[i][j]=1;
    if(i>0 && go(i-1,j)==0)
        s[i][j]=1;
    if(j>0 && go(i,j-1)==0)
        s[i][j]=1;
    if(i>0 && j>0 && go(i-1,j-1)==0)
        s[i][j]=1;
    return s[i][j];
}
main()
{
    int i,j;
    u[0][0]=1;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(u[i][j]==0)
                go(i,j);
            printf("%d ",s[i][j]);
        }
        puts("");
    }
    while(scanf("%d %d",&i,&j)==2)
        printf("%d\n",s[i][j]);
}
