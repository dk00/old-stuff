#include<cstdio>
struct Q
{
    int x,y;
}q[100000];
int map[200][200];
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
inline int dis2(int x1,int y1,int x2,int y2)
{
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
main()
{
    int i,j,k,m,r,c,nx,ny;
    while(1)
    {
        scanf("%d %d",&r,&c);
        if(r==0 && c==0)
            break;
        for(i=0;i<r;i++)
            for(j=0;j<r;j++)
                map[i][j]=0;
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            map[i][j]=-1;
        }
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d %d %d",&nx,&ny,&k);
            nx--,ny--,k*=k;
            for(i=0;i<r;i++)
                for(j=0;j<c;j++)
                    if(dis2(i,j,nx,ny)<=k)
                        map[i][j]=-1;
        }
        j=0;
        if(map[0][0]==0)
            q[j++]=(Q){0,0};
        for(i=0;i<j;i++)
        {
            nx=q[i].x,ny=q[i].y;
            if(nx==r-1 && ny==c-1)
                break;
            for(k=0;k<4;k++)
                if(map[nx+dx[k]][ny+dy[k]]==0 && nx+dx[k]>=0 && nx+dx[k]<r
                && ny+dy[k]>=0 && ny+dy[k]<c)
                {
                    q[j++]=(Q){nx+dx[k],ny+dy[k]};
                    map[nx+dx[k]][ny+dy[k]]=map[nx][ny]+1;
                }
        }
        if(nx==r-1 && ny==c-1)
            printf("%d\n",map[r-1][c-1]);
        else
            puts("Impossible.");
    }
}
