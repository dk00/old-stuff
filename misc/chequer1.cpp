#include<cstdio>
#include<cstdlib>

const int lv=2;
int player,cur_pl,score,ncheq[3],moves[3];
int bestx1,besty1,bestx2,besty2,ex_move[8][8][8][8];

int curt[3];

#include"chqctrl.h"
#include"cheqsc.h"

scoretable test[20];

int search(int d,int r)
{
    if(ncheq[3-cur_pl]==0)
        return 9999;
    if(ncheq[cur_pl]==0)
        return -9999;
    if(d>=lv*12 && (ncheq[1]+ncheq[2]>5&&ncheq[1]>1&&ncheq[2]>1))
        return test[curt[cur_pl]].calc(map)+
        (count(cur_pl)-count(3-cur_pl))*30;
    if(d>=lv*12)
        return test[curt[cur_pl]].calc(map)+
        (count(cur_pl)-count(3-cur_pl))*30;
    int i,j,k,sum=0,max=-20000000,tmp,pl=player,tmpx,tmpy,
    *dx=(int *)_mx[player-1],*dy=(int *)_my[player-1];
    check();
    int at=attack;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            if(map[i][j]==player || map[i][j]==player+2)
            {
                if(map[i][j]>2)k=4;
                else k=2;
                while(k--)
                {
                    curx=i,cury=j;
                    if(!able(curx+dx[k],cury+dy[k]))
                        continue;
                    attack=at;
                    select();
                    curx=i+dx[k],cury=j+dy[k];
                    if(map[curx][cury]==3-player ||
                    map[curx][cury]==5-player)
                        curx+=dx[k],cury+=dy[k];
                    if(mark[curx][cury])
                    {
                        tmpx=curx,tmpy=cury;
                        move();
                        if(attack==0)
                            tmp=r*search(d+12,-r);
                        else
                            tmp=search(d+3,r);
                        undo();
                        sum+=tmp;
                        ex_move[i][j][tmpx][tmpy]=tmp;
                        if(tmp>max)max=tmp;
                        if(able(tmpx,tmpy) && d==0 && (bestx1<0 ||
                      ex_move[bestx1][besty1][bestx2][besty2]<tmp))
                            bestx1=i,besty1=j,
                            bestx2=tmpx,besty2=tmpy;
                        if(tmp>9000)
                            return tmp;
                    }
                    selx=i,sely=j;
                }
            }
    return max;
}

int search_init()
{
    NOPRINT=1;
    bestx1=-1;
    int i,j,k,l;
    cur_pl=player;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            for(k=0;k<8;k++)
                for(l=0;l<8;l++)
                    ex_move[i][j][k][l]=-1000000;
    int r;
    if(player==1)r=1;
    else r=-1;
    int tmp=search(0,r);
    selx=sely=jmpx=jmpy=-1;
    check();
    NOPRINT=0;
    return tmp;
}

main()
{
    int c=-1,nx,ny;
    consoleinit();
    curx=0;
    cury=0;
    selx=-1;
    sely=-1;
    srand(time(NULL));
    for(int i=0;i<20;i++)
        test[i].load(i);
    while(c!=27)
    {
        newgame();
        moves[1]=count(1);
        moves[2]=count(2);
        score=search_init();
        show();
        movecursor(0,0);
        curt[1]=rand()%20;
        do curt[2]=rand()%20; while(curt[2]!=curt[1]);
        test[curt[1]].rev();
        while(moves[1]>0 && moves[2]>0 && nstep<90)
        {
            c=inkey();
            if(c=='r' || c=='R' || c==27)
                break;
            if((c=='u' || c=='U') && nstep>0)
            {
                undo(--nstep);
                show();
                selx=sely=-1;
                check();
                moves[1]=count(1);
                moves[2]=count(2);
                movecursor(0,0);
            }
            if(c==UP)
                movecursor(-1,0);
            if(c==DOWN)
                movecursor(1,0);
            if(c==LEFT)
                movecursor(0,-1);
            if(c==RIGHT)
                movecursor(0,1);
            if(c==13 && player==1)
            {
                
                if(mark[curx][cury]==0)
                    select();
                else
                {
                    check();
                    move();
                    if(map[curx][cury]==player+2)
                        score=score;
                    nx=curx,ny=cury;
                    score=search_init();
                    curx=nx,cury=ny;
                    if(map[curx][cury]==player ||
                    map[curx][cury]==player+2)
                        select();
                }
                
            }
            if(player==2){
                movecursor(bestx1-curx,besty1-cury);
                curx=bestx1,cury=besty1;
                select();
                //c=inkey();
                movecursor(bestx2-curx,besty2-cury);
                move();
                moves[1]=count(1);
                moves[2]=count(2);
                nx=curx,ny=cury;
                score=search_init();
                curx=nx,cury=ny;
                    if(map[curx][cury]==player ||
                    map[curx][cury]==player+2)
                        select();
                //c=inkey();
            }
        }
        test[curt[1]].rev();
        //while(inkey()==-1);
    }
}
