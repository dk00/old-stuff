#include"scrctr1.h"
#include<ctime>
main()
{
    int c;
    coninit();
    while((c=inkey())!=27)
    {
        locate(0,0);
        if(c!=-1)cprintf("%d %05d",c,clock());
    }
}
