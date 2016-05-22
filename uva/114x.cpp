#include<stdio.h>
long m,n,wcost,grid[51][51],val[51][51],cost[51][51],score;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
class ball{
public:
    int x,y,d,life;
    void go();
}ball;
void ball::go()
{
    life--;
    if(life<=0)return;
    if(x+dx[d]<=1 || x+dx[d]>=m || y+dy[d]<=1 || y+dy[d]>=n)
    {
        life-=wcost;
        d=(d+3)%4;
    }
    else if(grid[x+dx[d]][y+dy[d]])
    {
        life-=cost[x+dx[d]][y+dy[d]];
        score+=val[x+dx[d]][y+dy[d]];
        d=(d+3)%4;
    }
    else
    {
        x+=dx[d];
        y+=dy[d];
    }
}
main()
{
    long i,j,p,sum;
    scanf("%ld %ld %ld %ld",&m,&n,&wcost,&p);
    for(sum=i=0;i<m;i++)
        for(j=0;j<n;j++)grid[i][j]=0;
    while(p--)
    {
        scanf("%ld %ld",&i,&j);
        grid[i][j]=1;
        scanf("%ld %ld",&val[i][j],&cost[i][j]);
    }
    while(scanf("%ld %ld %ld %ld",&ball.x,&ball.y,&ball.d,&ball.life)!=EOF)
    {
        for(score=0;ball.life>0;ball.go());
        printf("%ld\n",score);
        sum+=score;
    }
    printf("%ld\n",sum);
}
