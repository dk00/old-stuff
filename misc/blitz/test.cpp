#include<cstdio>
#include<vector>
#include<cstring>
#include<windows.h>
using namespace std;
const int BW = 510, BH = 419;
HWND target;
BOOL CALLBACK Proc(HWND window, LPARAM p = NULL) {
  if (target != NULL) return false;
  const int MIN_W = 510, MIN_H = 419;
  RECT rect;
  GetWindowRect(window, &rect);
  int width = rect.right - rect.left, height = rect.bottom - rect.top;
  if (height < MIN_H || width < MIN_W) return true;
  char buf[99];
  GetClassName(window, buf, sizeof(buf));
  if (width == MIN_W && height == MIN_H && !strcmp(buf, "NativeWindowClass")) {
    target = window;
    return false;
  }
  EnumChildWindows(window, Proc, NULL);
  return true;
}

unsigned toPos(int x, int y) {
  return (368-x)*510 + 168+y;
}

int Capture(HWND hWnd, unsigned r[][320]) {
  printf("%X\n", hWnd);
  RECT rect;
  GetWindowRect(hWnd, &rect);
  HDC dc = GetDC(hWnd);
  HDC mdc = CreateCompatibleDC(dc);
  HBITMAP hbmp = CreateCompatibleBitmap(dc, rect.right-rect.left, rect.bottom-rect.top);
  SelectObject(mdc, hbmp);
  BitBlt(mdc, 0, 0, rect.right-rect.left, rect.bottom-rect.top, dc, 0, 0, SRCCOPY);
  BITMAP bmp;
  GetObject(hbmp, sizeof(BITMAP), &bmp);

  BITMAPFILEHEADER   bmfHeader;    
  BITMAPINFOHEADER   bi;

  bi.biSize = sizeof(BITMAPINFOHEADER);    
  bi.biWidth = bmp.bmWidth;    
  bi.biHeight = bmp.bmHeight;  
  bi.biPlanes = 1;    
  bi.biBitCount = 32;    
  bi.biCompression = BI_RGB;    
  bi.biSizeImage = 0;  
  bi.biXPelsPerMeter = 0;    
  bi.biYPelsPerMeter = 0;    
  bi.biClrUsed = 0;    
  bi.biClrImportant = 0;

  DWORD dwBmpSize = bmp.bmWidth*bmp.bmHeight*4;
  unsigned *buf = new unsigned[dwBmpSize/4];
  GetDIBits(mdc, hbmp, 0,
      (UINT)bmp.bmHeight,
      buf,
      (BITMAPINFO *)&bi, DIB_RGB_COLORS);
  HANDLE hFile = CreateFile("captureqwsx.bmp",
      GENERIC_WRITE,
      0,
      NULL,
      CREATE_ALWAYS,
      FILE_ATTRIBUTE_NORMAL, NULL);   
  DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
  bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER); 
  bmfHeader.bfSize = dwSizeofDIB; 
  bmfHeader.bfType = 0x4D42;
  DWORD dwBytesWritten = 0;
  WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
  WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
  WriteFile(hFile, (LPSTR)buf, dwBmpSize, &dwBytesWritten, NULL);
  CloseHandle(hFile);
  int i, j;
  for (i = 0; i < 320; ++i)
    for (j = 0; j < 320; ++j)
      r[i][j] = buf[toPos(i, j)]&0x00ffffff;
  DeleteObject(hbmp);
  DeleteObject(mdc);
  ReleaseDC(hWnd, dc);
  return 0;
}
unsigned res[320][320];

void Split(unsigned c, unsigned& r, unsigned& g, unsigned& b) {
  r = c >> 16;
  g = (c >> 8)&0xFF;
  b = c&0xFF;
}

void Find() {
  target = NULL;
  EnumWindows(Proc, NULL);
  Capture(target, res);
  int i, j, x, y;
  for (x = 0; x < 320; x += 40) {
    for (y = 0; y < 320; y += 40) {
      unsigned r, g, b, sr = 0, sg = 0, sb = 0;
      for (i = 0; i < 40; ++i)
        for (j = 0; j < 40; ++j) {
          Split(res[x+i][y+j], r, g, b);
          if (r > 127 || g > 127 || b> 127)
            sr += r, sg += g, sb += b;
        }
      j = ((sr>>15)<<8)|((sg>>15)<<4)|(sb>>15);
      printf("%03X ", j);
    }
    puts("");
  }
}

main() {
  Find();
}
