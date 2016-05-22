#include<cstdio>
int n,m,u[51][51],map[51][51],s[255],dx[]={0,-1,0,1},dy[]={-1,0,1,0};
int go(int x,int y,int k)
{
    if(u[x][y])return 0;
    u[x][y]=k;
    int i,sum=1;
    for(i=0;i<4;i++)
        if((1<<i)&~map[x][y])
            sum+=go(x+dx[i],y+dy[i],k);
    return sum;
}
main()
{
    freopen("castle.in","r",stdin);
    freopen("castle.out","w",stdout);
    int i,j,k,max;
    char soln[100];
    scanf("%d %d",&m,&n);
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&map[i][j]);
    for(i=max=0,k=1;i<n;i++)
        for(j=0;j<m;j++)
            if(!u[i][j])
                max>?=(s[k]=go(i,j,k++));
    printf("%d\n%d\n",k-1,max);
    for(j=m-1;j>=0;j--)
        for(i=0;i<n;i++)
        {
            if(j+1<m && u[i][j]!=u[i][j+1] && s[u[i][j]]+s[u[i][j+1]]>=max)
            {
                max=s[u[i][j]]+s[u[i][j+1]];
                sprintf(soln,"%d %d E",i+1,j+1);
            }
            if(i && u[i][j]!=u[i-1][j] && s[u[i][j]]+s[u[i-1][j]]>=max)
            {
                max=s[u[i][j]]+s[u[i-1][j]];
                sprintf(soln,"%d %d N",i+1,j+1);
            }
        }
    printf("%d\n%s\n",max,soln);
    scanf(" ");
}
/*
PROB: castle
LANG: C++
*/
