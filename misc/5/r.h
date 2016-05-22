#include<allegro.h>
// IO var
int mw,mh,boardlen;
int stx,sty,gridlen;
int white,black,grey,green,blue[4],red[4];
enum {Nothing=-2,Exit=-1,Put,NewGame,Undo,Search,Save};

// Game ctrl var
const int dx[]={-1,-1,0,1,1,1,0,-1},dy[]={0,1,1,1,0,-1,-1,-1};
struct pt{short x,y;} move[225];
unsigned char pl,isai[2],win[2],map[15][15];
int ns,boardsize,grx,gry;

// AI var
class darray
{
public:
    int n,count,tn[226],ed[226];
    short num[15][15],map[15][15];
    bool tmp2[3000];
    pt tmp,s[3000],tmp1[3000];
    int npt(){return ed[n];}
    void ins(short x,short y)
    {
        tmp1[tn[n]]=(pt){x,y};tmp2[tn[n]++]=1;
        if(!num[x][y]++)
            s[map[x][y]=ed[n]++]=(pt){x,y};
    }
    void del(short x,short y)
    {
        tmp1[tn[n]]=(pt){x,y};tmp2[tn[n]++]=0;
        if(num[x][y]<=0)
            return;
        if(--num[x][y])
            return;
        else num[x][y]=0;
        int i=map[x][y];
        s[i]=s[--ed[n]];
        map[s[i].x][s[i].y]=i;
    }
    void prev()
    {
        int i,x,y;
        n--;
        while(tn[n]-->tn[n-1])
        {
            i=map[x=tmp1[tn[n]].x][y=tmp1[tn[n]].y];
            if(!tmp2[tn[n]] && !num[x][y]++)
                s[map[x][y]=ed[n]++]=(pt){x,y};
            if(tmp2[tn[n]] && !--num[x][y])
            {
                s[i]=s[--ed[n]];
                map[s[i].x][s[i].y]=i;
            }
        }
        tn[n]++;
    }
    void next(){n++;ed[n]=ed[n-1],tn[n]=tn[n-1];}
    pt& operator[](int k){return s[k];}
};
pt Best,ptmp,togo[225];
short Level;
short c_score[15][15];
short ref[15][15],use[15][15],u3[15][15],u4[15][15],u5[15][15];
short gst[226],ged[226],tn[2][226],sc[2][226];
darray evil[2][4];  //0->three  1->four 2->Four 3->five

// IO func
void readcfg();
void init();
void drawboard();
void mark(int,int,int s=1);
void drawgrid(int c,int x=grx,int y=gry);
int  readinput();
void setcolor();
void click();

// Game ctrl func
inline bool ab(int,int);
void newgame();
void getwin(int r=1);
void put(int x=grx,int y=gry,int r=1,int i=-1);
void undo(int r=1);
bool count(int,int);

// AI Func
void check();

void readcfg()
{
    mw=800;
    mh=600;
    boardsize=15;
    boardlen=541;
    Level=6;
    isai[0]=0,isai[1]=1;
}
