#define _MSC_VER 1
#include"puzzle.h"
puzzle test;
main()
{
    int c;
    test.get();
    test.calc_init();
    consoleinit();
    cls();
    while(1)
    {
        c=inkey();
        if(c==27)
            break;
        if(c==DOWN)test.move(0);
        if(c==RIGHT)test.move(1);
        if(c==UP)test.move(2);
        if(c==LEFT)test.move(3);
        test.show();
    }
}
