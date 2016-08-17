#include<cstdio>
int n,m,dx[]={1,1,1,0,-1,-1,-1,0},dy[]={1,0,-1,1,0,-1,1,-1};
char map[1001][1001];
int go(int x,int y)
{
    if(x<0 || x>=n || y<0 || y>=m || map[x][y]!='*')return 0;
    map[x][y]='.';
    int i,sum=1;
    for(i=0;i<8;i++)
        sum+=go(x+dx[i],y+dy[i]);
    return sum;
}
main()
{
    int i,j,k;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(i=0;i<n;i++)
            scanf("%s",map[i]);
        for(i=k=0;i<n;i++)
            for(j=0;j<m;j++)
                if(go(i,j)==1)k++;
        printf("%d\n",k);
    }
}
