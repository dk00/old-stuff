#include<allegro.h>
#include<ctime>
#include<cstdlib>
#define UCHAR unsigned char
enum {Exit=-1,Newgame,Put,Undo,Inc,Dec,Search,Rec,Change};
const char name[][7]={"Human","CPU  "};
const signed char dx[]={-1,-1,0,1,1,1,0,-1},dy[]={0,1,1,1,0,-1,-1,-1};
const int glb=-20000000,gub=20000000;
char negtiveone=-1;
short Level=6,Player[2]={0,1};
short *ns2,dflag=0,rflag=1,undocount;
struct pt{char x,y;bool operator==(pt a){return(x==a.x && y==a.y);}};
struct setter
{
    char x,y,d;
    setter(char x1,char y1,char d1):x(x1),y(y1),d(d1){}
    char &operator()(char s[15][15])
    {
        if(x>=0 && x<15 && y>=0 && y<15)
            return s[x][y];
        return negtiveone;
    }
    void operator+=(short k){x+=k*dx[d],y+=k*dy[d];}
    void operator-=(short k){*this+=-k;}
    void operator++(){x+=dx[d],y+=dy[d];}
    void operator--(){x-=dx[d],y-=dy[d];}
    pt operator[](short u){return(pt){x+dx[d]*u,y+dy[d]*u};}
    pt topt(){return (pt){x,y};}
};
struct xlist
{
    short *ns;
    short n,rec,num[15][15],ref[15][15],p[225],i,j,na[225],nr[225];
    pt s[225],add[1000],rem[1000];
    void clear()
    {
        rec=1,n=na[0]=ns[0]=0;
        for(int i=0;i<225;i++)
        {
            s[i]=(pt){i/15,i%15};
            p[i]=i;
            ref[s[i].x][s[i].y]=i;
            num[s[i].x][s[i].y]=0;
        }
    }
    xlist(short *ns1=ns2):ns(ns1){clear();}
    void operator+=(pt a)
    {
        if(rec)add[na[*ns]++]=a;
        if(!num[a.x][a.y]++)
        {
            i=ref[a.x][a.y];
            j=p[i],p[i]=p[n],p[n]=j;
            ref[s[p[i]].x][s[p[i]].y]=i;
            ref[s[p[n]].x][s[p[n]].y]=n++;
        }
    }
    void operator-=(pt a)
    {
        if(rec)rem[nr[*ns]++]=a;
        if(!--num[a.x][a.y])
        {
            --n;
            i=ref[a.x][a.y];
            j=p[i],p[i]=p[n],p[n]=j;
            ref[s[p[i]].x][s[p[i]].y]=i;
            ref[s[p[n]].x][s[p[n]].y]=n;
        }
    }
    void operator++(){na[*ns]=na[*ns-1],nr[*ns]=nr[*ns-1];}
    void operator--()
    {
        rec=0;
        while(nr[*ns]>nr[*ns-1])
            *this+=rem[--nr[*ns]];
        while(na[*ns]>na[*ns-1])
            *this-=add[--na[*ns]];
        rec=1;
    }
    pt operator[](short n){return s[p[n]];}
    short operator()(pt a){return num[a.x][a.y];};
};
bool vl(int x,int y);
#include"screen.h"
#include"input.h"
#include"board.h"
#include"ai.h"
int main()
{
    allegro_init();
    short c,pl,ns,flag1=0;
    ns2=&ns;
    Screen xout;
    Input xin(&xout);
    Board map(&xin,&xout,&ns,&pl);
    xin.q=map.list;
    load_data();
    pl=0,map.clear();
    undocount=1;
    srand(time(NULL));
    while(1)
    {
        xout.print(145,700,"AI Level %d",Level);
        xout.print(76,710,"%c1P:%s",
        map.fwts[0]?'*':' ',name[Player[0]]);
        xout.print(116,710,"%c2P:%s",
        map.fwts[1]?'*':' ',name[Player[1]]);
        c=xin.getinput();
        if(c==Exit)
            break;
        if(c==Put)
        {
            if(Player[pl])
            {
                pt best=map.search();
                map.put(best.x,best.y,pl),pl=!pl;
                if(map.fwts[!pl])
                    xout.notice(best.x,best.y,red);
                else if(map.bnum4[ns][pl]+map.bl5[pl].n)
                    xout.notice(best.x,best.y,yellow);
                else
                    xout.notice(best.x,best.y,grey);
            }
            else if(map.put(xout.fx,xout.fy,pl))
                pl=!pl;
            if(map.win(!pl))
                allegro_message("Player %d win!",!pl+1);
        }
        if(c==Undo)
        {
            undocount=1;
            pl=!pl,map.undo();
        }
        if(c==Newgame)
            pl=ns=0,map.clear();
        if(c==Search)
        {
        }
        if(c==Inc)Level++;
        if(c==Dec)Level--;
        if(c==Rec)
        {
            char name[1000];
            sprintf(name,"rec%05d.txt",rand());
            map.write(name);
        }
        if(c==Change)
            Player[0]=!Player[0],Player[1]=!Player[1];
    }
}
END_OF_MAIN()
