#include"info.h"
#include"io.h"
#include"gamectrl.h"
main()
{
    int c,a,ai[]={0,0};
    io_init();
    setboard(15,15);
    start();
    while(1)
    {
        c=input();
        if(c<0)
            break;
        if(c==1)
        {
            if(map[curx][cury]==0)
                a=move();
            if(a==3)
            {
                print(21,oy+10,7,"Player %d win!",pl);
                anykey();
                print(21,oy+10,7,"             ",pl);
                start();
            }
            pl=!pl;
        }
        if(c==2)start();
        if(c==3)undo(),refresh();
    }
}
