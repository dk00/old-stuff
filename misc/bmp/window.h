#ifndef _WINDOW_H
#define _WINDOW_H
#include<windows.h>
class Window
{
    MSG messages;
    WNDCLASSEX wincl;
    int Funster;
public:
    HWND hwnd;
    int w,h;
    Window(const char *name,HINSTANCE hinst,int F);
    void show();
    void test();
    int mes();
};
#endif
