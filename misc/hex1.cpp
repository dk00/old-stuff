#include<cstdio>
int n,m,sum,max,map[99][99],mark[99][99],best[99][99];
const int dx[][6]={{-1,-1,0,0,1,1},{-1,-1,0,0,1,1}},
          dy[][6]={{-1,0,-1,1,-1,0},{0,1,-1,1,0,1}};
bool able(int x,int y)
{
    return(x>=0 && x<n && y>=0 && y<m && map[x][y]==1);
}
int go(int i)
{
    if(sum>max)
    {
        for(int j=n*m-1;j>=0;j--)
            best[j/m][j%m]=map[j/m][j%m];
        max=sum;
    }
    int j,p,tmp;
    for(;i<m*n;i++)
    {
        if(map[i/m][i%m]!=1)
            continue;
        p=(i/m)%2;
        for(j=tmp=0;j<6;j++)
        {
            if(able(i/m+dx[p][j],i%m+dy[p][j]) &&
            mark[i/m+dx[p][j]][i%m+dy[p][j]]++==0)
                tmp++;
        }
        map[i/m][i%m]=2;
        sum+=tmp-2;
        if(mark[i/m][i%m])
            sum--;
        if(tmp>2)
            go(i+1);
        if(mark[i/m][i%m])
            sum++;
        sum-=tmp-2;
        map[i/m][i%m]=1;
        for(j=0;j<6;j++)
            if(able(i/m+dx[p][j],i%m+dy[p][j]))
                mark[i/m+dx[p][j]][i%m+dy[p][j]]--;
    }
    return max;
}
main()
{
    int i,j;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=sum=max=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                scanf("%d",&map[i][j]);
                mark[i][j]=0;
                if(map[i][j]>0)
                    sum+=map[i][j]*2;
            }
        go(0);
        printf("%d.%d\n",max/2,5*(max%2));
        for(i=0;i<n;i++)
        {
            if(i%2)
                putchar(' ');
            for(j=0;j<m;j++)
            {
                if(best[i][j]==2)
                    printf("¡¯");
                else if(best[i][j]==1)
                    printf("¡C");
                else printf("  ");
            }
            puts("");
        }
    }
}
