#include<cstdio>
const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
struct pt{int x,y;}q[50];
char ch[]="NESW";
int u,x2,y2,s[8][8],p[8][8];
void print(int x,int y)
{
    if(p[x][y]<5)
    {
        print(x-dx[p[x][y]],y-dy[p[x][y]]);
        putchar(ch[p[x][y]]);
    }
}
main()
{
    int i,j,k,x1,y1,x3,y3,x4,y4;
    while(scanf("%d %d %d %d",&q[0].y,&q[0].x,&y2,&x2)==4 && x1+y1)
    {
        for(i=1;i<=6;i++)
            for(j=1;j<=6;j++)
                s[i][j]=15,p[i][j]=-1;
        for(i=1;i<=6;i++)
            s[i][1]&=~8,s[i][6]&=~2,
            s[1][i]&=~1,s[6][i]&=~4;

        for(i=0;i<3;i++)
        {
            scanf("%d %d %d %d",&y3,&x3,&y4,&x4);
            if(x3>x4)
                j=x3,x3=x4,x4=j;
            if(y3>y4)
                j=y3,y3=y4,y4=j;
            if(x3==x4)
                for(y3++;y3<=y4;y3++)
                    s[x3][y3]&=~4,s[x3+1][y3]&=~1;
            else
                for(x3++;x3<=x4;x3++)
                    s[x3][y3]&=~2,s[x3][y3+1]&=~8;
        }
        p[q[0].x][q[0].y]=5;
        for(i=0,j=1;i<j;i++)
        {
            for(k=0;k<4;k++)
                if((s[q[i].x][q[i].y]&(1<<k)) &&
                p[q[i].x+dx[k]][q[i].y+dy[k]]<0)
                    p[q[i].x+dx[k]][q[i].y+dy[k]]=k,
                    q[j++]=(pt){q[i].x+dx[k],q[i].y+dy[k]};
        }
        print(x2,y2);
        puts("");
    }
}
