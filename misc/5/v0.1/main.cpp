#include"r.h"
#include"io.h"
#include"ai.h"
#include"gamectrl.h"
int main()
{
    int c;
    init();
    setscore();
    newgame();
    while((c=readinput())!=-1)
    {
            
        if(c==Undo)
            undo();
        if(c==NewGame)
            newgame();
        if(c==Put)
        {
            put();
            check();
            search();
            textprintf_ex(screen,font,0,32,black,white,
            "(%3d,%3d)",Best.x,Best.y);
        }
        if(isai[pl])
        {
            mark(Best.x,Best.y);
            put();
            check();
            /*search();
            textprintf_ex(screen,font,0,32,black,white,
            "(%3d,%3d)",Best.x,Best.y);*/
        }
    }
}
END_OF_MAIN()
