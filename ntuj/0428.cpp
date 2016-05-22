#include<queue>
#include<cstdio>
using namespace std;
const int inf=2140000000,N=99;
int d[4][N][N],dx[]={1,0,-1,0},dy[]={0,-1,0,1};
struct pt{
    int x,y,k,c;
    bool operator<(pt a)const{return d[k][x][y]>d[a.k][a.x][a.y];}
};
int n,m,c[N][N];
char val(int x,int y){return x>=0 && x<n && y>=0 && y<m;}
main()
{
    int i,j,k,z,nx,ny,x[9];
    while(scanf("%d %d",&m,&n)>0 && n+m)
    {
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                scanf("%d",&c[i][j]);
                for(k=0;k<4;k++)
                    d[k][i][j]=inf;
            }
        for(i=0;i<4;i++)
            scanf("%d",x+i);
        d[3][0][0]=0;
        priority_queue<pt> h;
        h.push((pt){0,0,3,0});
        while(h.size())
        {
            pt p=h.top();
            h.pop();
            if(p.c!=d[p.k][p.x][p.y])continue;
            for(i=0;i<4;i++)
            {
                k=(p.k+i)%4;
                if(!val(nx=p.x+dx[k],ny=p.y+dy[k]))continue;
                z=x[i];
                if(c[p.x][p.y]==i)z=0;
                if(d[p.k][p.x][p.y]+z<d[k][nx][ny])
                    d[k][nx][ny]=d[p.k][p.x][p.y]+z,
                    h.push((pt){nx,ny,k,d[p.k][p.x][p.y]+z});
            }
        }
        for(i=0,j=inf;i<4;i++)
            if(d[i][n-1][m-1]<j)j=d[i][n-1][m-1];
        printf("%d\n",j);
    }
}
