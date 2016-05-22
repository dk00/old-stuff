#include"window$.h"
#include"grp.h"
#include"game.h"
hex s;
void refresh()
{
    for(int i=0;i<61;i++)
        unit(pos[i].x,pos[i].y,s[i]);
}
main()
{
    grpinit();
    board();
    int i,c,cx,cy,ox,oy,sx,sy,f=0,sel=0,end=0,tmp;
    cx=cy=4;
    s.reset();
    refresh();
    unit(cx,cy,0,1);
    while(1)
    {
        ox=cx,oy=cy;
        c=waitkey();
        if(c==Esc)break;
        if(c==Up)cx--;
        if(c==Down)cx++;
        if(c==Left)cy--;
        if(c==Right)cy++;
        if(c==Back)
            s.undo(),refresh(),f=1;
        if(c==Enter || c==Spc)
        {
            if(end)
                s.reset(),refresh(),f=1,end=0;
            else if(sel==1)
            {
                if(!s[(pt){cx,cy}])
                {
                    for(i=1;i<=18;i++)
                        if(d[i]+(pt){sx,sy}==(pt){cx,cy})
                            break;
                    if(i<=18)
                    {
                        tmp=s.move((pt){sx,sy},i);
                        if(tmp<0)MesBar("Invalid move");
                        else sel=0,refresh(),f=1;
                    }
                }
                if(sx==cx && sy==cy)
                    sel=0, unit(cx,cy,s[(pt){cx,cy}],1);
            }
            else if(sel==0 && s[(pt){cx,cy}]==s.pl)
            {
                sel=1,sx=cx,sy=cy;
                unit(cx,cy,s[(pt){cx,cy}],2);
            }
        }
        cx=(cx+9)%9;
        if(cx<5)cy=(cy+cx+5)%(cx+5);
        else cy=cx-4+(cy+9-2*cx+8)%(9-cx+4);
        if(cx-ox || cy-oy || f)
        {
            if(sel)
            {
                if(cx==sx && cy==sy)
                    unit(sx,sy,s[(pt){sx,sy}],2);
                else
                    unit(sx,sy,s[(pt){sx,sy}],1),
                    unit(cx,cy,s[(pt){cx,cy}],1);
                if(ox-sx || oy-sy)
                    unit(ox,oy,s[(pt){ox,oy}]);
            }
            else
                unit(ox,oy,s[(pt){ox,oy}]),
                unit(cx,cy,s[(pt){cx,cy}],1);
            f=0;
            printf(4,55,2,"Player %d     ",s.pl);
            printf(5,55,2,"%d,%d(%d)",cx,cy,s[(pt){cx,cy}]);
            printf(6,55,2,"%d,%d",s.copy[s.pl][num0((pt){cx,cy})],
            s.jmp[s.pl][num0((pt){cx,cy})]);
        }
        end=s.end();
        if(end)
            printf(4,55,2,"Player %d Win!",end);
    }
}
