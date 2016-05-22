#include<cstdio>
const char dx[]={1,0,-1,0},dy[]={0,1,0,-1};
char map[99][99];
int n,m,d[99][99];
double load[99][99];
struct pt{int x,y;}q[9999];
char valid(int x,int y)
{
    return(x>=0 && x<n && y>=0 && y<m && map[x][y]=='.');
}
int go(int x,int y,char ed,double w)
{
    if(d[x][y]==0)return 1;
    int sum=0;
    for(int i=0;i<4;i++)
        if(valid(x+dx[i],y+dy[i]) && d[x][y]-1==d[x+dx[i]][y+dy[i]])
            sum+=go(x+dx[i],y+dy[i],ed,w);
    if(map[x][y]!=ed)
        load[x][y]+=w*sum;
    return sum;
}
int go(int x,int y)
{
    if(d[x][y]==0)return 1;
    int sum=0;
    for(int i=0;i<4;i++)
        if(valid(x+dx[i],y+dy[i]) && d[x][y]-1==d[x+dx[i]][y+dy[i]])
            sum+=go(x+dx[i],y+dy[i]);
    return sum;
}
void go(char st,char ed,double w)
{
    int i,j,k,nx,ny,ex,ey;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
        {
            d[i][j]=n*m;
            if(map[i][j]==st)
                q[0]=(pt){i,j},map[i][j]='.';
            if(map[i][j]==ed)map[ex=i][ey=j]='.';
        }
    d[q[0].x][q[0].y]=0;
    for(i=0,j=1;i<j;i++)
        for(k=0;k<4;k++)
        {
            nx=q[i].x+dx[k],ny=q[i].y+dy[k];
            if(valid(nx,ny) && d[q[i].x][q[i].y]+1<d[nx][ny])
                d[nx][ny]=d[q[i].x][q[i].y]+1,q[j++]=(pt){nx,ny};
        }
    i=ex,j=ey;
out:go(i,j,ed,w/go(i,j));
    map[q[0].x][q[0].y]=st;
    map[i][j]=ed;
    load[i][j]-=w;
}
main()
{
    int i,j,k;
    char tmp[99];
    while(scanf("%d %d",&n,&m)==2 && n+m)
    {
        for(i=0;i<n;i++)
        {
            scanf("%s",map[i]);
            for(j=0;j<m;j++)
                load[i][j]=0;
        }
        while(scanf("%s %d",tmp,&k) &&(tmp[0]!='X' || tmp[1]!='X' || k>0))
            if(k)go(tmp[0],tmp[1],k);
        for(i=0;i<n;i++)
        {
            printf("%6.2lf",load[i][0]);
            for(j=1;j<m;j++)
                printf(" %6.2lf",load[i][j]);
            puts("");
        }
    }
}
