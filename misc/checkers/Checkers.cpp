#include"grp.h"
#include"game.h"
#include"..\window$.h"
board s;
char map[8][8];
const char dx[4]={1,1,-1,-1},dy[4]={1,-1,1,-1};
inline void refresh()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            s.draw(i,j,0);
}
void mark(int cx,int cy,int d=0)
{
    for(int i=0;i<4;i++)
        if(s.t[cx][cy][i]==1 && !s.at[s.pl])
            map[cx+dx[i]][cy+dy[i]]=d?i+1:0;
        else if(s.t[cx][cy][i]==2)
            map[cx+dx[i]*2][cy+dy[i]*2]=d?i+1:0;
}
main()
{
    grpinit();
    drawboard();
    int i,j;
    s.grp=1;
    s.reset();
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            s.draw(i,j);
    int c,cx,cy,ox,oy,sx,sy,sel,f;
    cx=cy=sel=0,ox=oy=-1;
    while(1)
    {
        if(cx-ox || cy-oy || f)
        {
            if(sel)
            {
                if(cx==sx && cy==sy)
                    drawp(sx,sy,s.s[sx][sy],s.active(sx,sy),11);
                else if(map[cx][cy])
                    drawp(cx,cy,s.s[cx][cy],0,10);
                else s.show(cx,cy,1);
            }
            else s.show(cx,cy);
        }
        printf(6,58,2,"Player: %d",s.pl);
        printf(7,58,2,"AT: %2d:%2d",s.at[0],s.at[1]);
        c=waitkey();
        if(c==Esc)break;
        ox=cx,oy=cy,f=0;
        if(c==Up)cx--;
        if(c==Left)cy--;
        if(c==Right)cy++;
        if(c==Down)cx++;
        if(c==Enter)
        {
            if(sel)
            {
                if(cx==sx && cy==sy)
                {
                    sel=0;
                    mark(sx,sy);
                }
                else if(map[cx][cy])
                {
                    sel=map[cx][cy]-1;
                    mark(sx,sy);
                    s.move(sx,sy,sel),sel=0;
                    refresh();
                }
                f=1;
            }
            else if(!sel && s.s[cx][cy]%2==s.pl && s.active(cx,cy))
            {
                sel=1,sx=cx,sy=cy;
                mark(cx,cy,1);
                f=1;
            }
        }
        cx=(cx+8)%8;
        cy=(cy+8)%8;
        if(cx-ox || cy-oy || f)
        {
            if(sel)
            {
                if(ox==sx && oy==sy)
                    drawp(ox,oy,s.s[ox][oy],s.active(ox,oy),3);
                else if(map[ox][oy])
                    drawp(ox,oy,s.s[ox][oy],0,2);
                else s.draw(ox,oy);
            }
            else s.draw(ox,oy,1);
        }
    }
}
