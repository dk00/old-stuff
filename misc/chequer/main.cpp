#include<time.h>
#include"io.h"
#include"gamectrl.h"
#include"ai.h"
main()
{
    srand(time(NULL));
    int c,sc,px[200],py[200],nx[200],ny[200],player[2]={0,1};
    init();
    setboard(8,8);
    ai_init(),start(),calc();
    selx=lx=-1,d2=0;
    pl=0,cmd[' ']=1;
    if(player[pl])
        sc=search_init();
    while(1)
    {
        /*if(abs(sc)>36)
        {
            print(21,32,7,"player%d win!     ",pl);
            anykey();
            start();
        }*/
        if(player[pl])
        {
            movecur(bx1,by1),select();
            copy(bx1,by1,bx2,by2);
            d2++;
            if(!move(bx1,by1,bx2,by2))pl=!pl;
            if(player[pl])
                sc=search_init();
            if(player[pl])
                anykey();
            continue;
        }
        if((c=input())<0)break;
        if(c==1)
        {
            if(mark[curx][cury]==39)
            {
                copy(px[d2]=selx,py[d2]=sely,nx[d2]=curx,ny[d2]=cury);
                d2++;
                if(!move(selx,sely,curx,cury))pl=!pl,sc=search_init();
                else select();
            }
            else select();
        }
        if(c==2)start();
        if(c==3)
        {
            --d2;
            undo(px[d2],py[d2],nx[d2],ny[d2]);
            refresh();
        }
        if(c==4)pl=!pl,search_init();
    }
}
