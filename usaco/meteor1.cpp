#include<cstdio>
const int inf=9999,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
struct pt
{
    int x,y;
}q[90900];
int nil,map[301][301],d[301][301];
int& s(int a[][301],int x,int y)
{
    if(x<0 || x>300 || y<0 || y>300)return nil;
    return a[x][y];
}
main()
{
    int i,j,k,n,t,x,y;
    while(scanf("%d",&n)>0)
    {
        for(i=0;i<=300;i++)
            for(j=0;j<=300;j++)
                d[i][j]=map[i][j]=inf;
        while(n--)
        {
            scanf("%d %d %d",&i,&j,&t);
            s(map,i,j)<?=t;
            for(k=0;k<4;k++)
                s(map,i+dx[k],j+dy[k])<?=t;
        }
        q[0]=(pt){0,0};
        d[0][0]=0;
        for(i=0,j=1;i<j;i++)
        {
            x=q[i].x,y=q[i].y;
            if(map[x][y]>=inf)break;
            for(k=0;k<4;k++)
                if(d[x][y]+1<s(map,x+dx[k],y+dy[k]) && d[x][y]+1<d[x+dx[k]][y+dy[k]])
                    d[x+dx[k]][y+dy[k]]=d[x][y]+1,q[j++]=(pt){x+dx[k],y+dy[k]};
        }
        printf("%d\n",map[x][y]>=inf?d[x][y]:-1);
    }
}
