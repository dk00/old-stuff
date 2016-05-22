#include<cstdio>
using namespace std;
const int N=3001,M=3000001,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int n,m,map[N][N],s[M];
inline int valid(int x,int y){return(x>=0 && x<n && y>=0 && y<m);}
void go(int x,int y)
{
    int i,c=map[x][y];
    map[x][y]=-1;
    for(i=0;i<4;i++)
        if(valid(x+dx[i],y+dy[i]) && map[x+dx[i]][y+dy[i]]==c)
            go(x+dx[i],y+dy[i]);
}
main()
{
    int i,j,K;
    freopen("pd.in","r",stdin);
    while(scanf("%d %d %d",&n,&m,&K)==3){
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                scanf("%d",&map[i][j]);
        for(i=0;i<=K;i++)
            s[i]=0;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                if(map[i][j]>0){
                    s[map[i][j]]++;
                    go(i,j);
                }
        for(i=1;i<=K;i++)
            printf("%d --- %d\n",i,s[i]);
    }
}
