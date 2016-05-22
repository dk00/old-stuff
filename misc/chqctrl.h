#define _MSC_VER 1
#include"scrctrl.h"

const char chequer[][3]={"  ","¡³","¡´","¡¸","¡¹"};
const int _dx=4,_dy=23,
          _mx[][4]={{1,1,-1,-1},{-1,-1,1,1}},
          _my[][4]={{1,-1,1,-1},{1,-1,1,-1}};
char map[8][8],mark[8][8],rec[99][8][8],rec1[99][8][8],rpl[100];
int attack,curx,cury,selx,sely,jmpx,jmpy,nstep,rcn1[99],rcn2[99];
int NOPRINT=0;

BOOL print(int x,int y,PCHAR s, ...)
{
    if(NOPRINT)
        return 0;
    if(x>=0 && y>=0)
        locate(x,y);
	va_list arg;
	char result[300];
	va_start(arg,s);
	vsprintf(result,s,arg);
	va_end(arg);
	return myPuts(result);
}

int able(int x,int y)
{
    return (x>=0 && x<8 && y>=0 && y<8 && (x+y)%2);
}


void newgame()
{
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            map[i][j]=0;
    for(i=0;i<3;i++)
        for(j=1-i%2;j<8;j++,j++)
            map[i][j]=1;
    for(i=5;i<8;i++)
        for(j=1-i%2;j<8;j++,j++)
            map[i][j]=2;
    player=1;
    ncheq[1]=ncheq[2]=12;
    attack=0;
    nstep=0;
    jmpx=jmpy=-1;
}

void copy(int rn=-1)
{
    if(rn<0)
        rn=nstep;
    rpl[rn]=player;
    rcn1[rn]=ncheq[1];
    rcn2[rn]=ncheq[2];
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            rec[rn][i][j]=map[i][j],
            rec1[rn][i][j]=mark[i][j];
}

void undo(int rn=-1)
{
    if(rn<0)
        rn=--nstep;
    player=rpl[rn];
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            map[i][j]=rec[rn][i][j],
            mark[i][j]=rec1[rn][i][j];
    ncheq[1]=rcn1[rn];
    ncheq[2]=rcn2[rn];
}

void show()
{
    int i,j;
    print(_dx+0,_dy+0,"¢z¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢{\n");
    print(_dx+1,_dy+0,"¢x");
    for(j=0;j<8;j++)
        print(-1,-1,"%s¢x",chequer[map[0][j]]);
    print(-1,-1,"\n");
    for(i=1;i<8;i++)
    {
        print(_dx+i*2,_dy,"¢u¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢t");
        print(_dx+i*2+1,_dy,"¢x");
        for(j=0;j<8;j++)
            print(-1,-1,"%s¢x",chequer[map[i][j]]);
        puts("");
    }
    print(_dx+16,_dy,"¢|¢w¢r¢w¢r¢w¢r¢w¢r¢w¢r¢w¢r¢w¢r¢w¢}");
}

void putcheq(int x,int y,char *s=NULL)
{
    if(s==NULL)
        print(_dx+x*2+1,_dy+y*4+2,"%s",chequer[map[x][y]]);
    else
        print(_dx+x*2+1,_dy+y*4+2,"%s",s);
}

void movecursor(int x,int y)
{
    if(curx!=selx || cury!=sely)
        color(C_LIGHTGRAY,C_BLACK);
    else
        color(C_WHITE,C_BLUE);
    if(mark[curx][cury])
        color(C_WHITE,C_GREEN);
    putcheq(curx,cury);
    curx=(curx+x+8)%8;
    cury=(cury+y+8)%8;
    if(mark[curx][cury] || (curx==selx && cury==sely))
        color(C_BLACK,C_WHITE);
    else
        color(C_BLACK,C_LIGHTGRAY);
    putcheq(curx,cury);
    color(C_LIGHTGRAY,C_BLACK);
    print(17+_dx,_dy,"(%2d,%2d) (%2d,%2d) (%d) player%d ",
    bestx1,besty1,bestx2,besty2,map[curx][cury],player);
    if(attack)
        print(-1,-1,"*");
    else
        print(-1,-1," ");
    print(18+_dx,_dy,"(%2d,%2d) ",moves[1],moves[2]);
    if(selx>-1 && sely>-1 && mark[curx][cury] &&
    ex_move[selx][sely][curx][cury]>-1000000)
        print(-1,-1,"(%5d)",ex_move[selx][sely][curx][cury]);
    else
        print(-1,-1," %5d ",score);
}

int setcheq(int x,int y,int set)
{
    int sum=0;
    int k,c1,c2,*dx=(int *)_mx[player-1],*dy=(int *)_my[player-1];
    if(set==0)
        c1=C_LIGHTGRAY,c2=C_BLACK;
    else
        c1=C_WHITE,c2=C_GREEN;
    if(map[x][y]>2)k=4;
    else k=2;
    for(int i=0;i<k;i++)
    if(able(x+dx[i],y+dy[i]))
    {
        if(map[x+dx[i]][y+dy[i]]==0 && attack==0)
        {
            color(c1,c2),putcheq(x+dx[i],y+dy[i]);
            mark[x+dx[i]][y+dy[i]]=set;
            sum++;
        }
        else if((map[x+dx[i]][y+dy[i]]==3-player ||
        map[x+dx[i]][y+dy[i]]==5-player) &&
        able(x+2*dx[i],y+2*dy[i]) && map[x+dx[i]*2][y+dy[i]*2]==0)
        {
            color(c1,c2),putcheq(x+dx[i]*2,y+dy[i]*2);
            mark[x+2*dx[i]][y+2*dy[i]]=set;
            sum++;
        }
    }
    color(C_LIGHTGRAY,C_BLACK);
    return sum;
}

void select()
{
    if(map[curx][cury]==0 || map[curx][cury]%2!=2-player)
        return;
    if(selx>=0 && sely>=0)
    {
        color(C_LIGHTGRAY,C_BLACK);
        putcheq(selx,sely);
        setcheq(selx,sely,0);
    }
    selx=curx,sely=cury;
    color(C_BLACK,C_WHITE);
    putcheq(selx,sely);
    if((jmpx<0 && jmpy<0) || (selx==jmpx && sely==jmpy))
        setcheq(selx,sely,1);
}

void check()
{
    attack=0;
    int i,j,k,m,*dx=(int *)_mx[player-1],*dy=(int *)_my[player-1];
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
        {
            if(map[i][j]==player)
                m=2;
            else if(map[i][j]==player+2)
                m=4;
            else m=0;
            for(k=0;k<m;k++)
                if(able(i+dx[k],j+dy[k]) &&
                (map[i+dx[k]][j+dy[k]]==3-player ||
                map[i+dx[k]][j+dy[k]]==5-player) &&
                able(i+2*dx[k],j+2*dy[k]) &&
                map[i+dx[k]*2][j+dy[k]*2]==0)
                {
                    attack=1;
                    return;
                }
        }
}

int count(int pl)
{
    int tmp=player;
    player=pl;
    int i,j,sum=0,tx,ty,atk;
    atk=attack;
    tx=jmpx,ty=jmpy;
    attack=0;
    jmpx=-1,jmpy=-1;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            if(map[i][j]==pl || map[i][j]==pl+2)
                sum+=setcheq(i,j,0);
    attack=atk;
    jmpx=tx,jmpy=ty;
    player=tmp;
    return sum;
}

int move()
{
    int prev=attack;
    setcheq(selx,sely,0);
    copy(nstep++);
    setcheq(selx,sely,0);
    if(abs(curx-selx)>1)
    {
        map[(curx+selx)/2][(cury+sely)/2]=0;
        color(C_LIGHTGRAY,C_BLACK);
        putcheq((curx+selx)/2,(cury+sely)/2);
        if(player==1)
            ncheq[2]--;
        else
            ncheq[1]--;
        jmpx=curx,jmpy=cury;
    }
    map[curx][cury]=map[selx][sely];
    if((map[curx][cury]==1 && curx==7) ||
    (map[curx][cury]==2 && curx==0))
        map[curx][cury]+=2;
    map[selx][sely]=0;
    color(C_WHITE,C_BLUE);
    putcheq(curx,cury);
    color(C_LIGHTGRAY,C_BLACK);
    putcheq(selx,sely);
    selx=-1,sely=-1;
    check();
    if(jmpx==curx && jmpy==cury && attack && setcheq(curx,cury,0))
    {
        select();
        return 0;
    }
    player=3-player;
    jmpx=jmpy=-1;
    check();
    return 1;
}
