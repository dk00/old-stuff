#include<cstdio>
int n,u;
int s[101][101][101];
inline char valid(int x,int y,int z)
{return(x>=0 && x<=n && y>=0 && y<=n && s[x][y][z]<=0);}
inline char go(int x,int y,int z)
{
    s[x][y][z]=u;
    if(valid(2*y-x+1,2*x-y-1,z) && go(2*y-x+1,2*x-y-1,z))return 1;
    if(valid(y,x,z) && go(y,x,z))return 1;
    if(valid(x,z,y) && go(x,z,y))return 1;
    if(valid(z,y,x) && go(z,y,x))return 1;
    return 0;
}
main()
{
    int i,j,k,x1,y1,z1,x2,y2,z2;
    while(scanf("%d",&n) && n)
    {
        u=0;
        for(i=0;i<=n;i++)
            for(j=0;j<=n;j++)
                for(k=0;k<n;k++)
                    s[i][j][k]=0;
        for(i=0;i<=n;i++)
            for(j=0;j<=n;j++)
                if(valid(i,j,3*n/2-i-j))
                    ++u,go(i,j,3*n/2-i-j);
        for(i=0;i<=n;i++)
        {
            for(j=0;j<=n;j++)
                printf("%2d ",s[i][j][3*n/2-i-j]);
            puts("");
        }
    }
}
