#include<cstdio>
char map[5][6],ans[5][6]={"11111","01111","00x11","00001","00000"};
int x,y,score,bound,next,
dx[]={1,2,1,2,-1,-2,-1,-2},dy[]={2,1,-2,-1,2,1,-2,-1},
dis[5][5]={{1,1,1,2,2},{1,1,1,1,2},{1,1,1,1,1},
{2,1,1,1,1},{2,2,1,1,1}};
int path[12][2];
inline bool dfs(int d)
{
    int i=d+score;
    if(i>bound)
    {
        if(i<next)
            next=i;
        return 0;
    }
    if(!score)
        return 1;
    int x1=x,y1=y,x2,y2;
    for(i=0;i<8;i++)
    {
        x2=x1+dx[i],y2=y1+dy[i];
        if(x2>=0 && x2<5 && y2>=0 && y2<5)
        {
            path[d][0]=x1,path[d][1]=y1;
            if(map[x2][y2]!=ans[x2][y2])
                score-=dis[x2][y2];
            if(map[x2][y2]!=ans[x1][y1])
                score+=dis[x1][y1];
            map[x1][y1]^=map[x2][y2]^=map[x1][y1]^=map[x2][y2];
            x=x2,y=y2;
            if(dfs(d+1))
                return 1;
            x=x1,y=y1;
            map[x1][y1]^=map[x2][y2]^=map[x1][y1]^=map[x2][y2];
            if(map[x2][y2]!=ans[x2][y2])
                score+=dis[x2][y2];
            if(map[x2][y2]!=ans[x1][y1])
                score-=dis[x1][y1];
        }
    }
    return 0;
}
main()
{
    int i,j,t,n=5;
    scanf("%d",&t),getchar();
    while(t--)
    {
        for(i=score=0;i<n;i++)
        {
            gets(map[i]);
            for(j=0;j<n;j++)
            {
                if(map[i][j]==' ')
                {
                    x=i,y=j;
                    continue;
                }
                if(map[i][j]!=ans[i][j])
                    score+=dis[i][j];
            }
        }
        next=score;
        do bound=next,next=22;
        while(bound<21 && !dfs(0));
        if(bound<21)
            printf("Solvable in %d move(s).\n",bound);
        else
            puts("Unsolvable in less than 11 move(s).");
    }
}
