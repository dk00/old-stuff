#include<cstdio>
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int n,m;
char map[9][9],u[64][64][64][64];
int valid(int x,int y){return(x>=0 && x<n && y>=0 && y<m && map[x][y]!='#');}
char go(int x1,int y1,int x2,int y2,int d)
{
    if(d<0)return -1;
    if(!valid(x2,y2))return 1;
    if(u[x1][y1][x2][y2] || u[x2][y2][x1][y1])return 1;
    u[x1][y1][x2][y2]=u[x2][y2][x1][y1]=1;
    int i,j,tmp=0;
    for(i=0;i<4;i++)
    {
        if(x1+dx[i]==x2 && y1+dy[i]==y2)
        {
            u[x1][y1][x2][y2]=u[x2][y2][x1][y1]=0;
            return 1;
        }
        j=go(x2,y2,x1+dx[i],y1+dy[i],d-1);
        if(j==-1)tmp=-1;
        if(!j)
        {
            u[x1][y1][x2][y2]=u[x2][y2][x1][y1]=0;
            return 1;
        }
    }
    u[x1][y1][x2][y2]=u[x2][y2][x1][y1]=0;
    return tmp;
}
main()
{
    int i,j,x1,y1,x2,y2;
    while(scanf("%d %d",&n,&m)==2)
    {
        x1=-1;
        for(i=0;i<n;i++)
        {
            scanf("%s",map[i]);
            for(j=0;j<m;j++)
                if(map[i][j]=='P')
                {
                    if(x1==-1)x1=i,y1=j;
                    else x2=i,y2=j;
                }
        }
        for(i=0;i<n*m;i++)
            for(j=0;j<n*m;j++)
                u[i/m][i%m][j/m][j%m]=0;
        for(i=0;i<1000000;i++)
        {
            j=go(x1,y1,x2,y2,i);
            if(j!=-1)break;
            j=go(x2,y2,x1,y1,i);
            if(j!=-1)break;
        }
        printf("%d\n",i);
        if(j)
            puts("Alice wins.");
        else puts("Bob wins.");
    }
}
