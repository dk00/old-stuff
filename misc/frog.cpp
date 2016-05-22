#include<cstdio>
int n,m,sum,find,s[12][12],dx[]={-1,0,1,0},dy[]={0,-1,0,1},
rev[]={2,3,0,1};
char dir[]="uldr",path[200];
void go(int step,int x,int y)
{
    if(step==sum)
    {
        find=1;
        path[step]=0;
        puts(path);
    }
    s[x][y]=0;
    int nx,ny;
    for(int i=0;i<4 && find==0;i++)
    {
        if(step && path[step-1]==dir[rev[i]])continue;
        nx=x+dx[i],ny=y+dy[i];
        while(nx>=0 && nx<n && ny>=0 && ny<m)
        {
            if(s[nx][ny]==1)
            {
                path[step]=dir[i];
                go(step+1,nx,ny);
                break;
            }
            nx+=dx[i],ny+=dy[i];
        }
    }
    s[x][y]=1;
}
main()
{
    int i,j;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=sum=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                scanf("%d",&s[i][j]);
                if(s[i][j]==1)
                    sum++;
            }
        for(i=find=0;i<n;i++)
            for(j=0;j<m;j++)
                if(s[i][j]==2)
                    go(0,i,j);
    }
}
