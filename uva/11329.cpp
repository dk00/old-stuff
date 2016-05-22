#include<cstdio>
#include<cstdlib>
const int inf=16,dx[]={1,0,-1,0},dy[]={0,1,0,-1},c[4][7]={
    {0,3,2,6,1,5,4},
    {0,1,4,2,5,3,6},
    {0,4,2,1,6,5,3},
    {0,1,3,5,2,4,6},
};
char map[9][9],u[9],tmp[9],x_[]="V>^<";
char valid(int x,int y)
{
    return(x>=0 && x<4 && y>=0 && y<4);
}
int h(int x,int y)
{
    int i,j,sum=0,min=20;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(map[i][j]=='X')
                sum++,min<?=abs(i-x)+abs(j-y);
    if(!sum)return 0;
    return (sum+min-1)>?1;
}
void flip(int x,int y,int d)
{
    int i;
    for(i=1;i<=6;i++)
        tmp[c[d][i]]=u[i];
    for(i=1;i<=6;i++)
        u[i]=tmp[i];
    if(map[x+=dx[d]][y+=dy[d]]=='X' && u[3])
        return;
    if(map[x][y]=='X')
        map[x][y]='.',u[3]=1;
    else if(u[3])
        u[3]=0,map[x][y]='X';
}
void undo(int x,int y,int d)
{
    int i;
    if(u[3] && map[x][y]=='X');
    else if(u[3])
        u[3]=0,map[x][y]='X';
    else if(map[x][y]=='X')
        u[3]=1,map[x][y]='.';
    for(i=1;i<=6;i++)
        tmp[i]=u[c[d][i]];
    for(i=1;i<=6;i++)
        u[i]=tmp[i];
}
int now,next,min;
char go(int x,int y,int d)
{
    int tmp=d+h(x,y);
    if(tmp>now)
    {
        next<?=tmp;
        return 0;
    }
    if(tmp==d)
    {
        min<?=tmp;
        return 1;
    }
    int i;
    for(i=0;i<4;i++)
        if(valid(x+dx[i],y+dy[i]))
        {
            flip(x,y,i);
            if(go(x+dx[i],y+dy[i],d+1))
                return 1;
            undo(x+dx[i],y+dy[i],i);
        }
    return 0;
}
main()
{
    int i,j,sx,sy,T;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<4;i++)
        {
            scanf("%s",map[i]);
            for(j=0;map[i][j];j++)
                if(map[i][j]=='D')
                    map[sx=i][sy=j]='.';
        }
        for(i=1;i<=6;i++)u[i]=0;
        next=h(sx,sy);
        min=inf;
        while(next<inf)
        {
            now=next,next=inf;
            if(go(sx,sy,0))
                break;
        }
        if(next>=inf)
            puts("impossible");
        else
            printf("%d\n",min);
    }
}
