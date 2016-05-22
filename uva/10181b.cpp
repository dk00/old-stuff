#include<cstdio>
#include<cstdlib>
#define vaild(x,y) (x>=0 && x<n && y>=0 && y<n)
const int n=4,dx[]={1,0,-1,0},dy[]={0,1,0,-1},rev[]={2,3,0,1};
char path[1000],dirt[]="DRUL";
int x,y,step,score,next,bound,s[n][n],num[n*n][n][n];
bool dfs()
{
    if(step+score>bound)
    {
        if(step+score<next)
            next=step+score;
        return false;
    }
    if(!score)
    {
        return true;
        path[step]=0;
    }
    for(int i=0;i<4;i++)
        if(path[step-1]!=dirt[rev[i]] && vaild(x+dx[i],y+dy[i]))
        {
            score-=num[s[x][y]][x][y];
            s[x+dx[i]][y+dy[i]]=s[x][y];
            s[x+=dx[i]][y+=dy[i]]=0;
            score+=num[s[x][y]][x][y];
            path[step++]=dirt[i];
            if(dfs())
                return true;
            step--;
            score-=num[s[x][y]][x][y];
            s[x-dx[i]][y-dy[i]]=s[x][y];
            s[x-=dx[i]][y-=dy[i]]=0;
            score+=num[s[x][y]][x][y];
        }
    return false;
}
main()
{
    int i,j,k,l,t;
    scanf("%d",&t);
    for(k=n*n-2;k>=0;k--)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                num[k+1][i][j]=abs(k/n-i)+abs(k%n-j);
    while(t--)
    {
        for(i=l=score=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                scanf("%d",&s[i][j]);
                if(s[i][j]==0)
                {
                    x=i,y=j;
                    continue;
                }
                score+=num[s[i][j]][i][j];
                for(k=i*n+j;k>=0;k--)
                    if(s[k/n][k%n]>s[i][j])l++;
            }
        if((l+x+1)&1)
        {
            puts("This puzzle is not solvable.");
            continue;
        }
        step=1,bound=score;
        while(1)
        {
            next=1000;
            if(dfs())
                break;
            bound=next;
        }
        puts(path);
    }
}
