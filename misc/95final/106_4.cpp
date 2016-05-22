#include<cstdio>
const int dx[]={-3,-3,-1, 1, 3, 3, 1,-1},
          dy[]={-1, 1, 3, 3, 1,-1,-3,-3},
          px[]={-1,-1, 0, 0, 1, 1, 0, 0},
          py[]={ 0, 0, 1, 1, 0, 0,-1,-1},
          inf=20000;
int s[100][100];
struct pt
{
    int x,y;
}q[20000];
bool valid(int x,int y)
{
    return (x>=0 && x<100 && y>=0 && y<100 && s[x][y]>=0);
}
main()
{
    int i,j,k,n,nx,ny,ex,ey;
    for(i=0;i<100;i++)
        for(j=0;j<100;j++)
            s[i][j]=inf;
    freopen("in_4.txt","r",stdin);
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&ex,&ey);
        s[ex][ey]=-1;
    }
    scanf("%d %d",&q[0].x,&q[0].y);
    s[q[0].x][q[0].y]=0;
    scanf("%d %d",&ex,&ey);
    for(i=0,j=1;i<j;i++)
    {
        if(s[ex][ey]<inf)break;
        nx=q[i].x,ny=q[i].y;
        for(k=0;k<8;k++)
        {
            if(valid(nx+px[k],ny+py[k]) && valid(nx+dx[k],ny+dy[k]) &&
            s[nx][ny]+1<s[nx+dx[k]][ny+dy[k]])
            {
                q[j++]=(pt){nx+dx[k],ny+dy[k]};
                s[nx+dx[k]][ny+dy[k]]=s[nx][ny]+1;
            }
        }
    }
    if(s[ex][ey]<inf)
        printf("%d\n",s[ex][ey]);
    else
        puts("impossible");
}
