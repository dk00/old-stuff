#include<cstdio>
const int inf=270000,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
struct pt
{
    int x,y,k;
}q[inf];
char map[300][301];
int n,m,s[3][300][300];
void go(int x,int y,int px,int py,int l,int &j)
{
    int tmp=s[l-1][x][y]+1;
    for(int i=0;i<l;i++)
    {
        x+=px,y+=py;
        if(x<0 || x>=n || y<0 || y>=m || map[x][y]=='#')
            return;
    }
    if(tmp<s[l%3][x][y])
        s[l%3][x][y]=tmp,q[j++]=(pt){x,y,l%3};
}
main()
{
    int i,j,k,nx,ny,nk,tx,ty,ex,ey,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                for(k=0;k<3;k++)
                    s[k][i][j]=inf;
        for(i=0;i<n;i++)
        {
            scanf("%s",map[i]);
            for(j=0;j<m;j++)
                if(map[i][j]=='S')
                    s[0][i][j]=0,q[0]=(pt){i,j,0};
                else if(map[i][j]=='E')
                    ex=i,ey=j;
        }
        for(i=0,j=1;i<j;i++)
        {
            nx=q[i].x,ny=q[i].y,nk=q[i].k+1;
            for(k=0;k<4;k++)
                go(nx,ny,dx[k],dy[k],nk,j);
        }
        for(k=0,j=inf;k<3;k++)
            j<?=s[k][ex][ey];
        if(j<inf)printf("%d\n",j);
        else puts("NO");
    }
}

