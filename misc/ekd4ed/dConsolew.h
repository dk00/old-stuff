#ifndef dConsolew
#define dConsolew
#include<windows.h>
namespace scr
{
    enum {unchange=-1,black=0,blue,green,cyan,red,magenta,brown,lgray,darkgray,
    lblue,lgreen,lcyan,lred,lmagenta,yellow,white};
    HANDLE stdin,console;
    class screen
    {
        screen()
        {
	       stdin=GetStdHandle(STD_INPUT_HANDLE);
	       console=GetStdHandle(STD_OUTPUT_HANDLE);
        };
        
    };
}
#endif
