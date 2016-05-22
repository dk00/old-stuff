#include<windows.h>
#include"blitz.h"

struct DC_s{
  HWND hwnd;
  unsigned w, h;
  HDC DC, memDC;
  HBITMAP hbmp;
} GameWindow;

const int WindowW = 510, WindowH = 419, MarginX = 49, MarginY = 168;

BOOL CALLBACK Proc(HWND window, LPARAM p = NULL) {
  if (GameWindow.hwnd != NULL) return false;
  RECT rect;
  GetWindowRect(window, &rect);
  int width = rect.right - rect.left, height = rect.bottom - rect.top;
  if (height < WindowH || width < WindowW) return true;
  char buf[99];
  GetClassName(window, buf, sizeof(buf));
  if (width == WindowW && height == WindowH && !strcmp(buf, "NativeWindowClass")) {
    GameWindow.hwnd = window;
    return false;
  }
  EnumChildWindows(window, Proc, (LPARAM)NULL);
  return true;
}

unsigned *buf;
bool FindGameWindow() {
  EnumWindows(Proc, (LPARAM)NULL);
  if (GameWindow.hwnd == NULL) return false;
  RECT rect;
  GetWindowRect(GameWindow.hwnd, &rect);
  GameWindow.h = rect.bottom-rect.top;
  GameWindow.w = rect.right-rect.left;
  GameWindow.DC = GetDC(GameWindow.hwnd);
  GameWindow.memDC = CreateCompatibleDC(GameWindow.DC);
  GameWindow.hbmp = CreateCompatibleBitmap(GameWindow.DC, GameWindow.w, GameWindow.h);
  SelectObject(GameWindow.memDC, GameWindow.hbmp);
  unsigned BmpSize = GameWindow.w*GameWindow.h*4;
  buf = new unsigned[BmpSize/4];  
}

inline unsigned BmpPos(int x, int y) {
  const int sx = MarginX + BoardH*GridH - 1;
  return (sx-x)*WindowW + MarginY+y;
}

int GetRawBoard(unsigned r[][BoardW*GridW]) {
  BitBlt(GameWindow.memDC, 0, 0, GameWindow.w, GameWindow.h, GameWindow.DC, 0, 0, SRCCOPY);

  BITMAPINFOHEADER   bi;
  bi.biSize = sizeof(BITMAPINFOHEADER);
  bi.biWidth = GameWindow.w;
  bi.biHeight = GameWindow.h;
  bi.biPlanes = 1;
  bi.biBitCount = 32;
  bi.biCompression = BI_RGB;
  bi.biSizeImage = 0;
  bi.biXPelsPerMeter = 0;
  bi.biYPelsPerMeter = 0;
  bi.biClrUsed = 0;
  bi.biClrImportant = 0;

  unsigned BmpSize = GameWindow.w*GameWindow.h*4;
  GetDIBits(GameWindow.memDC, GameWindow.hbmp, 0, (UINT)GameWindow.h, buf, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

/*  HANDLE hFile = CreateFile("captureqwsx.bmp",
      GENERIC_WRITE,
      0,
      NULL,
      CREATE_ALWAYS,
      FILE_ATTRIBUTE_NORMAL, NULL);   
  BITMAPFILEHEADER   bmfHeader;
  DWORD dwSizeofDIB = BmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
  bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER); 
  bmfHeader.bfSize = dwSizeofDIB; 
  bmfHeader.bfType = 0x4D42;
  DWORD dwBytesWritten = 0;
  WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
  WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
  WriteFile(hFile, (LPSTR)buf, dwBmpSize, &dwBytesWritten, NULL);
  CloseHandle(hFile);*/

  int i, j;
  for (i = 0; i < BoardH*GridH; ++i)
    for (j = 0; j < BoardW*GridW; ++j)
      r[i][j] = buf[BmpPos(i, j)]&0x00ffffff;

  return 0;
}

#include<cstdio>

inline unsigned TranX(int x) {
  return MarginX + x*GridH + GridH/2;
}

inline unsigned TranY(int y) {
  return MarginY + y*GridW + GridW/2;
}

bool Select(int x, int y) {
  x = TranX(x);
  y = TranY(y);
  SendNotifyMessage (GameWindow.hwnd, WM_LBUTTONDOWN, MK_LBUTTON, y|(x<<16));
	SendNotifyMessage (GameWindow.hwnd, WM_LBUTTONUP, MK_LBUTTON, y|(x<<16));
}

bool SendMove(int x, int y, Dirc d) {
  int nx = x + dx[d], ny = y + dy[d];
  if (x < 0 || x >= BoardH || y < 0 || y >= BoardW || nx < 0 || nx >= BoardH || ny < 0 || ny >= BoardW)
    return false;
  x = TranX(x);
  y = TranY(y);
  nx = TranX(nx);
  ny = TranY(ny);
  SendNotifyMessage (GameWindow.hwnd, WM_LBUTTONDOWN, MK_LBUTTON, y|(x<<16));
  SendNotifyMessage (GameWindow.hwnd, WM_MOUSEMOVE, 0, ((y+ny)/2)|(((x+nx)/2)<<16));
  SendNotifyMessage (GameWindow.hwnd, WM_LBUTTONUP, 0, ny|(nx<<16));
}

void sleep(unsigned t) {
  Sleep(t);
}
