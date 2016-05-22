#include<stdio.h>
#include"window.h"
LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

Window::Window(const char *name,HINSTANCE hinst,int F){
    w=800,h=600;
    Funster=F;
    wincl.hInstance=hinst;
    wincl.lpszClassName=name;
    wincl.lpfnWndProc=WindowProcedure;
    wincl.style=CS_DBLCLKS;
    wincl.cbSize=sizeof(wincl);
    wincl.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    wincl.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
    wincl.hCursor=LoadCursor(NULL,IDC_ARROW);
    wincl.lpszMenuName=NULL;
    wincl.cbClsExtra=0;
    wincl.cbWndExtra=0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    RegisterClassEx(&wincl);
    hwnd = CreateWindowEx(0,"test00","test00",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,w,h,HWND_DESKTOP,NULL,hinst,NULL);
}
void Window::show()
{
    ShowWindow (hwnd, Funster);
}
void Window::test()
{
    PAINTSTRUCT ps;
	HDC hdc=BeginPaint(hwnd,&ps);

    char buf[2048];

	int x=50;
	int y=60;

	int len=sprintf(buf,"Hello World!");
	TextOut(hdc,x,y,buf,len);

	EndPaint(hwnd,&ps);
}
int Window::mes()
{
    while(GetMessage(&messages,NULL,0,0)){
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}
bool load(Window& W);
int WINAPI WinMain (HINSTANCE This,HINSTANCE Prev,LPSTR Arg,int Funster)
{
    Window w("test00",This,Funster);
    w.show();
    load(w);
    //w.test();
    return w.mes();
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message){                 /* handle the messages */
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
