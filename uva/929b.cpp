#include<list>
#include<cstdio>
const short inf=32767,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
struct pt
{
    short x,y;
};
using namespace std;
list<pt> s[18000];
short c[1000][1000],d[1000][1000];
list<pt>::iterator p[1000][1000];
int n,m;
char valid(int x,int y){return (x>=0 && x<n && y>=0 && y<m);}
main()
{
    int i,j,T,Max,nx,ny;
    list<pt>::iterator k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                scanf("%d",&c[i][j]);
                d[i][j]=inf;
            }
        for(i=Max=0;i<n;i++)
            Max+=c[i][0];
        for(j=1;j<m;j++)
            Max+=c[n-1][j];
        s[d[0][0]=c[0][0]].push_back((pt){0,0});
        for(i=c[0][0];i<=Max;i++)
        {
            for(k=s[i].begin();k!=s[i].end();k++)
                for(j=0;j<4;j++)
                {
                    nx=k->x+dx[j],ny=k->y+dy[j];
                    if(valid(nx,ny) && d[k->x][k->y]+c[nx][ny]<d[nx][ny])
                    {
                        if(d[nx][ny]<inf)s[d[nx][ny]].erase(p[nx][ny]);
                        s[d[nx][ny]=d[k->x][k->y]+c[nx][ny]].push_back((pt){nx,ny});
                        --(p[nx][ny]=s[d[nx][ny]].end());
                    }
                }
            s[i].clear();
        }
        for(;i<18000;i++)s[i].clear();
        printf("%d\n",d[n-1][m-1]);
    }
}
