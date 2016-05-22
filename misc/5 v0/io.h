#define _MSC_VER
#include"scrctrl.h"
int ox,oy,curx,cury,selx,sely;
int cmd[256],dirc[1000];
const char ch[][3]={"  ","¡³","¡´"};
void print(int x,int y,int c,PCHAR s, ...)
{
    locate(x,y),color(c);
	va_list arg;
	char result[300];
	va_start(arg,s);
	vsprintf(result,s,arg);
	va_end(arg);
	myPuts(result);
}
void io_init()
{
    consoleinit();
    cmd[13]=1,cmd[27]=-1,cmd['u']=3,cmd['c']=4;
    dirc[UP]=dirc[DOWN]=dirc[LEFT]=dirc[RIGHT]=1;
    dx[UP]=dy[LEFT]=-1,dx[DOWN]=dy[RIGHT]=1;
}
int _refresh=1;
void refresh(int x,int y)
{
    if(!_refresh)return;
    if(curx==x && cury==y)
        print(ox+x+1,oy+y*2+2,(mark[x][y]+136)&~15,"%s",ch[map[x][y]]);
    else
        print(ox+x+1,oy+y*2+2,mark[x][y],"%s",ch[map[x][y]]);
}
void refresh()
{
    for(int i=0;i<bh;i++)
        for(int j=0;j<bw;j++)
            refresh(i,j);
}
void movecur(int nx,int ny)
{
    nx=(nx+bh)%bh,ny=(ny+bw)%bw;
    curx+=nx,nx=curx-nx,curx-=nx;
    cury+=ny,ny=cury-ny,cury-=ny;
    refresh(curx,cury),refresh(nx,ny);
}
void setboard(int h,int w)
{
    bh=h,bw=w;
    int i,j;
    ox=(23-h)/2,oy=(76-2*w)/2;
    print(ox,oy,7,"¢~");
    for(j=oy+2;j<=oy+2*w;j+=2)
        print(ox,j,7,"¢w");
    print(ox,j,7,"¢¡");
    for(i=ox+1;i<ox+h+1;i++)
    {
        print(i,oy,7,"¢x");
        for(j=oy+2;j<=oy+w*2;j+=2)
            print(i,j,7,"  ");
        print(i,j,7,"¢x");
    }
    print(i,oy,7,"¢¢");
    for(j=oy+2;j<=oy+w*2;j+=2)
        print(i,j,7,"¢w");
    print(i,j,7,"¢£");
    movecur(7,7);
}
int input()
{
    int c;
    while(1)
    {
        locate(24,79);
        c=inkey();
        if(c<0)continue;
        if(cmd[c])
            return cmd[c];
        if(dirc[c])
            movecur(curx+dx[c],cury+dy[c]);
        locate(24,79);
    }
}
void anykey()
{
    print(22,27,7,"Press any key to continue");
    locate(24,79);
    while(inkey()<0);
    print(22,27,7,"                         ");
}
