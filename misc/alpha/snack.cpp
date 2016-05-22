#include<ctime>
#include<cstdlib>
#include"scrctr1.h"
char dx[]={1,0,-1,0},dy[]={0,1,0,-1},style[]="|-|-+*";
short sx,sy,h,w,map[100][100];
class node
{
    public:
    node *next;
    short x,y,d,t;
    void set(short x1,short y1){x=x1,y=y1;}
    void display(char a=1)
    {
        char c=style[d];
        if(t)c=style[4];
        if(a==2)c=style[5];
        locate(sx+x,sy+y);
        if(a)color(lGray,Black);
        else color(Black,Black);
        scprintf("%c",c);
        color(lGray,Black);
    }
    void move(short gen)
    {
        if(next==NULL && gen)
        {
            next=new node;
            next->x=x,next->y=y,next->d=d,next->t=0;
            next->next=NULL;
            next->display();
            gen--;
            x=(x+dx[d]+h)%h;
            y=(y+dy[d]+w)%w;
            map[x][y]=-1;
            return;
        }
        if(next==NULL)
        {
            map[x][y]=0;
            display(0);
        }
        x=(x+dx[d]+h)%h;
        y=(y+dy[d]+w)%w;
        map[x][y]=-1;
        if(next!=NULL)
        {
            next->move(gen);
            next->d=d;
        }
    }
};
class head:public node
{
    node *last;
    public:
    short grow;
    head(){grow=t=0,next=last=NULL;};
    short go(int nd,int g=0)
    {
        if(g)grow+=g;
        if(nd<0)nd=d;
        if((d+1)%4==nd || (d+3)%4==nd)
            d=nd,t=1;
        short tmp=map[(x+dx[d]+h)%h][(y+dy[d]+w)%w];
        if(tmp<0)return 1;
        if(tmp>0)
            grow=+tmp;
        if(grow)move(grow--);
        else move(0);
        display(2);
        if(next)next->t=t,t=0,next->display();
        if(tmp>0)return 2;
        return 0;
    }
}snack;
void drawboard()
{
    int i;
    color(Black,lGray);
    scprintf(sx-1,sy-1,"+");
    scprintf(sx-1,sy+w,"+");
    scprintf(sx+h,sy-1,"+");
    scprintf(sx+h,sy+w,"+");
    for(i=0;i<w;i++)
        scprintf(sx-1,sy+i,"-"),scprintf(sx+h,sy+i,"-");
    for(i=0;i<h;i++)
        scprintf(sx+i,sy-1,"|"),scprintf(sx+i,sy+w,"|");
    color(lGray,Black);
}
int interval;
void showinfo()
{
    scprintf(sx+h+1,sy,"interval: %4d grow: %2d",interval,snack.grow);
}
void gen()
{
    int i,j;
    while(1)
    {
        i=rand()%h,j=rand()%w;
        if(map[i][j]==0)
        {
            map[i][j]=1+rand()%5;
            scprintf(sx+i,sy+j,"%d",map[i][j]);
            return;
        }
    }
}
main()
{
    coninit();
    srand(time(NULL));
    short c;
    int i,j,st,d,g;
    sx=1,sy=1,h=20,w=75;
    for(i=0;i<h;i++)
        for(j=0;j<w;j++)
            map[i][j]=0;
    interval=500,d=-1,g=0;
    st=clock();
    snack.x=5,snack.y=25,snack.d=0;
    snack.display(2);
    drawboard(),showinfo();
    map[5][25]=-1;gen();
    while(1)
    {
        c=inkey();
        if(c==Esc)break;
        if(c==Down)d=0;
        if(c==Right)d=1;
        if(c==Up)d=2;
        if(c==Left)d=3;
        if(c=='=')interval+=20,showinfo();
        if(c=='-' && interval>20)interval-=20,showinfo();
        if(c==Space)g++;
        if(clock()-st>interval)
        {
            if(snack.go(d,g)==2)gen();
            g=0;
            d=-1,st=clock();
            showinfo();
            locate(24,78);
        }
    }
}
