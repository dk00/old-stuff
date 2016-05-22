// IO var
int mw,mh,boardlen;
int stx,sty,gridlen;
int white,black,grey,green;
enum {Nothing=-2,Exit=-1,Put,NewGame,Undo,Search};
// Game ctrl var
const int dx[]={-1,-1,0,1,1,1,0,-1},dy[]={0,1,1,1,0,-1,-1,-1};
struct pt{int x,y;} move[225];
unsigned char pl,isai[2],win[2],map[15][15];
int ns,boardsize,grx,gry;
// AI var
pt Best,ptmp,togo[225];
short Level;
short c_score[15][15];
short use[15][15];
short thrn[2][226],gst[226],ged[226],sc[2][226];

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
    Level=4;
    isai[0]=0,isai[1]=1;
}
