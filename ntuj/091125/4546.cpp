#include<cmath>
#include<queue>
#include<cstdio>
using namespace std;
const int N=105,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
const double inf=1e60;
struct pt{int x,y;}st,ed;
char u[N][N],map[N][N];
int n;
double d[N][N];
inline bool valid(int x,int y){return(x>=0 && x<n && y>=0 && y<n && map[x][y]!='#');}
double sp(double v)
{
    int i,j,nx,ny;
    double nd;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            d[i][j]=inf;
            u[i][j]=1;
        }

    queue<pt> Q;
    Q.push(st);
    d[st.x][st.y]=0;
    while(!Q.empty()){
        pt p=Q.front();
        Q.pop();
        u[p.x][p.y]=1;
        for(i=0;i<4;i++){
            nx=p.x+dx[i],ny=p.y+dy[i];
            if(dx[i])nd=d[p.x][p.y]+v;
            else nd=d[p.x][p.y]+100;
            if(valid(nx,ny) && nd<d[nx][ny]){
                d[nx][ny]=nd;
                if(u[nx][ny]){
                    u[nx][ny]=0;
                    Q.push((pt){nx,ny});
                }
            }
        }
    }
    return d[ed.x][ed.y];
}
main()
{
    int i,j,T,C=1;
    double L;
    scanf("%d",&T);
    while(T--){
        scanf("%lf %d%*c",&L,&n);
        for(i=0;i<n;i++){
            gets(map[i]);
            for(j=0;j<n;j++)
                if(map[i][j]=='S')
                    st.x=i,st.y=j;
                else if(map[i][j]=='E')
                    ed.x=i,ed.y=j;
        }
        double a,b,z;
        for(a=0,b=1000;a<b;){
            double k=sp((a+b)/2);
            if(fabs(k-L*100)<1e-5){
                z=(a+b)/2;
                break;
            }
            if(k>L*100)
                b=(a+b)/2;
            else a=(a+b)/2;
        }
        printf("Case #%d: %.3lf%%\n",C++,z);
    }
}
