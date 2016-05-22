#include<ctime>
#include<conio.h>
#include"scrctr1.h"
char teststr[]="colortestcolortest";
main()
{
    coninit();
    char x=0,c;
    while(1)
    {
        c=inkey();
        if(c!=-1)x=!x;
        locate(0,1);
        if(x)scprintf("*");
        else scprintf(" ");
        if(!x)scprintf("%06d     ",clock());
        if(c!=-1)
        {
            locate(1,1);
            scprintf("%d(%c)   ",c,c);
        }
    }
}
