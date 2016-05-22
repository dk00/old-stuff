#include<cstdio>
#include<algorithm>
using namespace std;
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int n,m,in,out,s[501][501],u[999][999];
struct pt
{
    int x,y,h;
    bool operator<(pt a)const{return h>a.h;}
}tmp[999999];
char valid(int x,int y)
{
    return(x>=0 && x<n && y>=0 && y<m);
}
void go(int x,int y)
{
    int i;
    u[x][y]=0;
    for(i=0;i<4;i++)
        if(valid(x+dx[i],y+dy[i]) && u[x+dx[i]][y+dy[i]]
        && s[x][y]>=s[x+dx[i]][y+dy[i]])
            go(x+dx[i],y+dy[i]);
}
main()
{
    int i,j,k,l,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=l=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                scanf("%d",&s[i][j]),u[i][j]=1;
                tmp[l++]=(pt){i,j,s[i][j]};
            }
        sort(tmp,tmp+l);
        in=out=0;
        for(k=0;k<l;k++)
            if(u[i=tmp[k].x][j=tmp[k].y])in++,go(i,j);
        for(i=l=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                s[i][j]*=-1,u[i][j]=1;
                tmp[l++]=(pt){i,j,s[i][j]};
            }
        sort(tmp,tmp+l);
        for(k=0;k<l;k++)
            if(u[i=tmp[k].x][j=tmp[k].y])out++,go(i,j);
        if(tmp[0].h==tmp[l-1].h)in=out=0;
        printf("%d\n",in>?out);
    }
}
