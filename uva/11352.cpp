#include<cstdio>
const int dx[]={0,1,1,1,0,-1,-1,-1},dy[]={1,1,0,-1,-1,-1,0,1},
kx[]={1,2,2,1,-1,-2,-2,-1},ky[]={2,1,-1,-2,-2,-1,1,2};
struct pt{int x,y;}q[40000];
int d[110][110];
char map[110][110];
main()
{
    int i,j,k,n,m,T,nx,ny;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=1;i<=n+2;i++)map[i][1]=map[i][m+2]=0;
        for(j=1;j<=m+2;j++)map[1][j]=map[n+2][j]=0;
        for(i=2;i<=n+1;i++)
        {
            scanf("%s",map[i]+2);
            for(j=2;j<=m+1;j++)
            {
                d[i][j]=n*m+1;
                if(map[i][j]=='A')
                    q[0]=(pt){i,j},d[i][j]=0;
            }
        }
        for(i=2;i<=n+1;i++)
            for(j=2;j<=m+1;j++)
                if(map[i][j]=='Z')
                    for(map[i][j]=k=0;k<8;k++)
                        if(map[i+kx[k]][j+ky[k]]=='.')
                            map[i+kx[k]][j+ky[k]]=0;
        for(i=0,j=1;i<j;i++)
        {
            if(map[nx=q[i].x][ny=q[i].y]=='B')break;
            for(k=0;k<8;k++)
                if(map[nx+dx[k]][ny+dy[k]] && d[nx][ny]+1<d[nx+dx[k]][ny+dy[k]])
                    d[nx+dx[k]][ny+dy[k]]=d[nx][ny]+1,
                    q[j++]=(pt){nx+dx[k],ny+dy[k]};
        }
        if(i<j)
            printf("Minimal possible length of a trip is %d\n",d[nx][ny]);
        else puts("King Peter, you can't go now!");
    }
}
