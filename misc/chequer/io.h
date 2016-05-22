#define _MSC_VER
#include"scrctrl.h"
int curx,cury,selx,sely,ox,oy,bh,bw;
int pl,lx,ly,num[2],jmp[2];
int cmd[27],dirc[1000],dx[1000],dy[1000],jnum[8][8];
int _sc[8][8][8][8];
int bx1,by1,bx2,by2;
char map[10][10],mark[10][10],
     ch[][3]={"  ","","¡³","¡´","¡¸","¡¹","¡¸","¡¹"};
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
void init()
{
    consoleinit();
    cmd[13]=1,cmd[27]=-1,cmd['r']=2,cmd['u']=3,cmd['c']=4;
    dirc[UP]=dirc[DOWN]=dirc[LEFT]=dirc[RIGHT]=1;
    dx[UP]=dy[LEFT]=-1,dx[DOWN]=dy[RIGHT]=1;
    dx[0]=dx[1]=1,dx[2]=dx[3]=-1;
    dy[0]=dy[2]=1,dy[1]=dy[3]=-1;
}
int _refresh=1;
void refresh(int x,int y)
{
    if(!_refresh)return;
    if(curx==x && cury==y)
        print(ox+x*2+1,oy+y*4+2,(mark[x][y]+136)&~15,"%s",ch[map[x][y]]);
    else
        print(ox+x*2+1,oy+y*4+2,mark[x][y],"%s",ch[map[x][y]]);
}
void refresh()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
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
    ox=(24-2*h)/2,oy=(76-4*w)/2;
    print(ox,oy,7,"¢~¢w");
    for(j=oy+4;j<oy+w*4;j+=4)
        print(ox,j,7,"¢s¢w");
    print(ox,j,7,"¢¡");
    for(i=ox+1;i<ox+h*2-2;i+=2)
    {
        print(i,oy,7,"¢x");
        for(j=oy+4;j<=oy+w*4;j+=4)
            print(i,j,7,"¢x  ");
        print(i+1,oy,7,"¢u¢w");
        for(j=oy+4;j<oy+w*4;j+=4)
            print(i+1,j,7,"¢q¢w");
        print(i+1,j,7,"¢t");
    }
    print(i,oy,7,"¢x");
    for(j=oy+4;j<=oy+w*4;j+=4)
        print(i,j,7,"¢x  ");
    print(++i,oy,7,"¢¢¢w");
    for(j=oy+4;j<oy+w*4;j+=4)
        print(i,j,7,"¢r¢w");
    print(i,j,7,"¢£");
    movecur(0,0);
}
int input()
{
    int c;
    while(1)
    {
        //debug info
        print(21,30,7,"player%d  %4d:%4d",pl,num[0],num[1]);
        /*print(22,22,7,"(%2d,%2d) (%2d,%2d) %d %d",
        curx,cury,selx,sely,map[curx][cury],jnum[curx][cury]);*/
        /*if(abs(_sc[selx][sely][curx][cury])<100)
            print(23,40,7,"%4d %d %d %d %d",
            _sc[selx][sely][curx][cury],bx1,by1,bx2,by2);
        else
            print(23,40,7,"---- %d %d %d %d",bx1,by1,bx2,by2);*/
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
