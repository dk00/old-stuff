#include"grp.h"
#include"game.h"
#include<cstring>
inline bool valid(char x,char y){return(x>=0 && x<8 && y>=0 & y<8);}
const char dx[4]={1,1,-1,-1},dy[4]={1,-1,1,-1}
            ,u[5][4]={{0,0,0,0},{1,1,0,0},{0,0,1,1},{1,1,1,1},{1,1,1,1}};
void board::reset()
{
    memset(s,0,sizeof(s));
    int i,j;
    pl=step=f=num[0]=num[1]=at[0]=at[1]=0;
    for(i=0;i<3;i++)
        for(j=1-i%2;j<8;j++,j++)
            ins(i,j,1,0),ins(8-i-1,8-j-1,2,0);

}
void board::ins(char x,char y,char c,char uu)
{
    s[x][y]=c;
    num[s[x][y]%2]++;
    char i,nx,ny,mx,my,ox,oy;
    for(i=0;i<4;i++)
    {
        ox=x-dx[i],oy=y-dy[i];
        nx=x+dx[i],ny=y+dy[i];
        mx=nx+dx[i],my=ny+dy[i];
        if(valid(mx,my) && t[mx][my][3-i]==2)
            t[mx][my][3-i]=0,at[s[mx][my]%2]--;
        if(valid(nx,ny) && s[nx][ny])
            t[nx][ny][3-i]=0;
        if(valid(nx,ny) && valid(ox,oy) && u[s[nx][ny]][3-i]
        && s[nx][ny] && !s[ox][oy] && s[nx][ny]%2!=s[x][y]%2)
            t[nx][ny][3-i]=2,at[s[nx][ny]%2]++;
        t[x][y][i]=0;
        if(!u[s[x][y]][i])continue;
        if(valid(nx,ny))
        {
            if(!s[nx][ny])t[x][y][i]=1;
            else if(s[nx][ny]%2!=s[x][y]%2 && s[nx][ny] && valid(mx,my) && !s[mx][my])
                t[x][y][i]=2,at[s[x][y]%2]++;
        }
    }
    if(uu)px[f]=x,py[f]=y,act[f++]=0;
}
void board::del(char x,char y,char uu)
{
    num[s[x][y]%2]--;
    if(uu)px[f]=x,py[f]=x,act[f]=1,cl[f++]=s[x][y];
    char i,nx,ny,mx,my,ox,oy;
    for(i=0;i<4;i++)
    {
        ox=x-dx[i],oy=y-dy[i];
        nx=x+dx[i],ny=y+dy[i];
        mx=nx+dx[i],my=ny+dy[i];
        if(valid(mx,my) && u[s[mx][my]][3-i] && s[nx][ny] && s[nx][ny]%2!=s[mx][my]%2)
            t[mx][my][3-i]=2,at[s[mx][my]%2]++;
        if(valid(nx,ny) && u[s[nx][ny]][3-i])
        {
            if(t[nx][ny][3-i]==2)at[s[nx][ny]%2]--;
            t[nx][ny][3-i]=1;
        }
        if(t[x][y][i]==2)at[s[x][y]%2]--;
        t[x][y][i]=0;
    }
    s[x][y]=0;
}
char board::move(char x,char y,char z)
{
    if(!t[x][y][z])return 0;
    char v=t[x][y][z],tmp=s[x][y];
    if(s[x+v*dx[z]][y+dy[z]*v]<=2 &&(x+v*dx[z]==0 || x+v*dx[z]==7))
    {
        ins(x+v*dx[z],y+dy[z]*v,tmp+2);
        tmp=-1;
    }
    else ins(x+v*dx[z],y+dy[z]*v,tmp);
    if(v>1)del(x+dx[z],y+dy[z]);
    del(x,y);
    p[step++]=f;
    x=x+v*dx[z],y=y+dy[z]*v;
    if(tmp>=0 && v>1)for(char i=0;i<4;i++)
        if(t[x][y][i]>1)return 2;
    pl=!pl;
    return 1;
}
void board::undo()
{
    step--;
    while(f>p[step-1])
        if(act[--f]==1)
            ins(px[f],py[f],cl[f],0);
        else
            del(px[f],py[f],0);
    pl=cl[f]%2;
}
void board::show(char x,char y,char l)
{
    if(s[x][y])
    {
        if(s[x][y]%2==pl)
            drawp(x,y,s[x][y],active(x,y),3);
        else
            drawp(x,y,s[x][y],active(x,y),4);
    }
    else
        drawp(x,y,s[x][y],active(x,y),7);
    if(l)return ;
    int i,j,nx,ny;
    for(i=0;i<4;i++)
        if(j=t[x][y][i])
        {
            nx=x+dx[i]*j,ny=y+dy[i]*j;
            if(s[x][y]%2==pl)
                drawp(nx,ny,s[nx][ny],active(nx,ny),2);
            else
                drawp(nx,ny,s[nx][ny],active(nx,ny),6);
        }
}
void board::draw(char x,char y,char l)
{
    drawp(x,y,s[x][y],active(x,y));
    if(!l)return;
    int i,j,nx,ny;
    for(i=0;i<4;i++)
        if(j=t[x][y][i])
        {
            nx=x+dx[i]*j,ny=y+dy[i]*j;
            drawp(nx,ny,s[nx][ny],active(nx,ny));
        }
}
