#include<windows.h>
HWND init(HINSTANCE hinst)
{
    char classname[]="test",winname[]="test";
    WNDCLASS WinClass;
    WinClass.style=0;
    WinClass.lpfnWndProc=DefWindowProc;
    WinClass.cbClsExtra=0;
    WinClass.cbWndExtra=0;
    WinClass.hInstance=hinst;
    WinClass.hIcon=0;
    WinClass.hCursor=LoadCursor(0,IDC_ARROW);
    WinClass.hbrBackground=reinterpret_cast<HBRUSH> (COLOR_WINDOW+1);
    WinClass.lpszMenuName=0;
    WinClass.lpszClassName=classname;
    RegisterClass(&WinClass);
    return CreateWindow(classname,winname,
    WS_SYSMENU,CW_USEDEFAULT,0,CW_USEDEFAULT,0,0,0,hinst,0);
}
int WINAPI WinMain
(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow)
{
    HWND win=init(hInst);
    ShowWindow(win,cmdShow);
    UpdateWindow(win);
    MSG msg;
    int status;
    while ((status=GetMessage(&msg,0,0,0))!=0)
    {
        if (status == -1)
            return -1;
        ::DispatchMessage (& msg);
    }
    return msg.wParam;
}
