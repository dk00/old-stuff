#include<queue>
#include<cstdio>
using namespace std;
struct pt{int x,y,s;void operator+=(pt a){x+=a.x,y+=a.y;}};
pt p,d[]={{1,0,0},{0,1,0},{-1,0,0},{0,-1,0}};
queue<pt> q;
int n,m,s[100][100];
char map[100][100];
bool able(pt a)
{
    return(a.x>=0 && a.x<n && a.y>=0 && a.y<m &&
    map[a.x][a.y]!='X' && s[a.x][a.y]==0);
}
main()
{
    int i,j,C=1,P,x1,x2,y1,y2;
    while(scanf("%d %d%c",&m,&n,map[0]) && n+m)
    {
        for(P=1,i=1;i<=n;i++)
            gets(map[i]+1);
        n+=2,m+=2;
        for(i=0;i<n;i++)
        {
            map[i][0]=' ';
            for(j=1;map[i][j];j++);
            for(;j<m;j++)
                map[i][j]=' ';
        }
        printf("Board #%d:\n",C++);
        while(scanf("%d %d %d %d",&y1,&x1,&y2,&x2) && x1+x2+y1+y2)
        {
            for(i=0;i<n;i++)
                for(j=0;j<m;j++)
                    s[i][j]=0;
            while(!q.empty())q.pop();
            q.push((pt){x1,y1,0});
            s[x1][y1]=1;
            map[x2][y2]++;
            while(!q.empty())
            {
                p=q.front();
                if(p.x==x2 && p.y==y2)
                    break;
                for(i=0;i<4;i++)
                {
                    pt now=p;
                    now+=d[i];
                    now.s++;
                    while(able(now))
                    {
                        q.push(now);
                        s[now.x][now.y]=now.s+1;
                        now+=d[i];
                    }
                }
                q.pop();
            }
            map[x2][y2]--;
            printf("Pair %d: ",P++);
            if(q.empty())
                puts("impossible.");
            else
                printf("%d segments.\n",p.s);
        }
    }
}
