// Blitz.cpp : 定義主控台應用程式的進入點。

#include<windows.h>


int Type[8][8];
int Mark[8][8];
HWND Handle;
HDC Browser;
DWORD StartTime;
BYTE Green, Red, Blue;
int Tools = 0;
int DelayTime;

int FindMove(int Step);
void FindHandle(void){
  HWND Temp = FindWindowEx(NULL, NULL, "Chrome_WidgetWin_0", "Facebook 上的 Bejeweled Blitz - Google 瀏覽器");
  Temp = FindWindowEx(Temp, NULL, "Chrome_WidgetWin_0", NULL);
  Temp = FindWindowEx(Temp, NULL, "Chrome_RenderWidgetHostHWND", NULL);

  HWND Temp2 = NULL, Temp3 = NULL;
  RECT Rect;
  Rect.bottom = Rect.left = Rect.right = Rect.top = 0;
  while(Rect.top - Rect.bottom != 384 && Rect.right - Rect.left != 510){
    Temp2 = FindWindowEx(Temp, Temp2, "WrapperNativeWindowClass", "");
    Temp3 = FindWindowEx(Temp2, NULL, "NativeWindowClass", "");
    if(Temp3 == NULL)
      break;
    GetWindowRect(Temp3, &Rect);
  }
  Handle = Temp3;

  if(Handle != NULL){
    printf("已取得 Handle: %08x\n", Handle);
    return;
  }

  Temp = FindWindowEx(NULL, NULL, "MozillaUIWindowClass", "Facebook 上的 Bejeweled Blitz - Mozilla Firefox");
  Temp = FindWindowEx(Temp, NULL, "MozillaWindowClass", NULL);
  Temp = FindWindowEx(Temp, NULL, "MozillaContentWindowClass", NULL);
  Temp = FindWindowEx(Temp, NULL, "MozillaWindowClass", NULL);

  Temp2 = NULL;
  Temp3 = NULL;
  Rect.bottom = Rect.left = Rect.right = Rect.top = 0;
  while(Rect.top - Rect.bottom != 384 && Rect.right - Rect.left != 510){
    Temp2 = FindWindowEx(Temp, Temp2, "MozillaWindowClass", NULL);
    Temp3 = FindWindowEx(Temp2, NULL, "GeckoPluginWindow", NULL);
    if(Temp3 == NULL)
      break;
    GetWindowRect(Temp3, &Rect);
  }
  Handle = Temp3;	

  if(Handle != NULL){
    printf("已取得 Handle: %08x\n", Handle);
    return;
  }
}

void GetRGB(int x, int y){
  COLORREF Pixel = GetPixel(Browser, x, y);
  Green = GetGValue(Pixel);
  Red = GetRValue(Pixel);
  Blue = GetBValue(Pixel);
}

  int Compare(int R1, int G1, int B1, int R2, int G2, int B2){
    if(R1 >= R2 - 30 && R1 <= R2 + 30 && G1 >= G2 - 30 && G1 <= G2 + 30 && B1 >= B2 - 30 && B1 <= B2 + 30)
      return 1;
    else
      return 0;
  }

int GetColor(int Row, int Column){
  int x, y;

  x = 168 + Row * 40;
  y = 49 + Column * 40;

  if(GetTickCount() - StartTime > 5000 || Row < 3 || Row > 4 || Column < 3 || Column > 4){
    GetRGB(x + 13, y + 21);
    if(Red != 255 || Green != 255 || Blue != 255){
      int local;
      for(local = 10; local < 30; local++){
        GetRGB(x + 20, y + local);
        if(Compare(Red, Green, Blue, 40, 40, 40))
          return 8;
        //				GetRGB(x + local, y + 20);
        //				if(Compare(Red, Green, Blue, 40, 40, 40))
        //					return 8;
      }
    }
  }

  GetRGB(x + 6, y + 29);
  if(Compare(Red, Green, Blue, 185, 0, 13)) // red
    return 1;
  GetRGB(x + 19, y + 20);
  if(Compare(Red, Green, Blue, 251, 27, 55)) // red
    return 1;
  GetRGB(x + 7, y + 21);
  if(Compare(Red, Green, Blue, 175, 12, 21)) // red
    return 1;

  GetRGB(x + 10, y + 30);
  if(Compare(Red, Green, Blue, 0, 244, 36)) // green
    return 3;
  GetRGB(x + 16, y + 15);
  if(Compare(Red, Green, Blue, 69, 254, 105)) // green
    return 3;
  GetRGB(x + 8, y + 21);
  if(Compare(Red, Green, Blue, 0, 171, 7)) // green
    return 3;

  GetRGB(x + 8, y + 34);
  if(Compare(Red, Green, Blue, 218, 0, 218)) // purple
    return 5;
  GetRGB(x + 19, y + 23);
  if(Compare(Red, Green, Blue, 237, 15, 237)) // purple
    return 5;
  GetRGB(x + 6, y + 21);
  if(Compare(Red, Green, Blue, 126, 14, 135)) // purple
    return 5;

  GetRGB(x + 12, y + 31);
  if(Compare(Red, Green, Blue, 252, 85, 0)) // orange
    return 6;
  GetRGB(x + 18, y + 25);
  if(Compare(Red, Green, Blue, 254, 119, 22)) // orange
    return 6;
  GetRGB(x + 7, y + 21);
  if(Compare(Red, Green, Blue, 237, 87, 0)) // orange
    return 6;

  GetRGB(x + 24, y + 3);
  if(Compare(Red, Green, Blue, 0, 53, 144)) // blue
    return 7;
  GetRGB(x + 17, y + 20);
  if(Compare(Red, Green, Blue, 17, 143, 254)) // blue
    return 7;
  GetRGB(x + 7, y + 21);
  if(Compare(Red, Green, Blue, 0, 110, 211)) // blue
    return 7;
  GetRGB(x + 29, y + 12);
  if(Compare(Red, Green, Blue, 2, 67, 181)) // blue
    return 7;

  GetRGB(x + 5, y + 19);
  if(Compare(Red, Green, Blue, 250, 211, 3)) // yellow
    return 2;
  GetRGB(x + 13, y + 29);
  if(Compare(Red, Green, Blue, 255, 254, 7)) // yellow
    return 2;
  GetRGB(x + 20, y + 19);
  if(Compare(Red, Green, Blue, 254, 250, 36)) // yellow
    return 2;
  GetRGB(x + 8, y + 21);
  if(Compare(Red, Green, Blue, 211, 207, 0)) // yellow
    return 2;

  GetRGB(x + 11, y + 31);
  if(Compare(Red, Green, Blue, 162, 162, 162)) // white
    return 4;
  GetRGB(x + 18, y + 18);
  if(Compare(Red, Green, Blue, 254, 254, 254)) // white
    return 4;
  GetRGB(x + 8, y + 21);
  if(Compare(Red, Green, Blue, 177, 177, 177)) // white
    return 4;

  return 0;
}

void ChooseItem(void){
  GetRGB(183, 147);
  if(Red == 16 && Green == 22 && Blue == 77 && Tools){
    SendMessage(Handle, WM_LBUTTONDOWN, MK_LBUTTON, 345 + 250 * 65536);
    SendMessage(Handle, WM_LBUTTONUP, 0, 345 + 250 * 65536);
    SendMessage(Handle, WM_LBUTTONDOWN, MK_LBUTTON, 252 + 348 * 65536);
    SendMessage(Handle, WM_LBUTTONUP, 0, 252 + 348 * 65536);
    StartTime = GetTickCount();
    printf("M\n");
  }

  GetRGB(159, 350);
  if(Red == 195 && Green == 68 && Blue == 147){
    SendMessage(Handle, WM_LBUTTONDOWN, MK_LBUTTON, 159 + 350 * 65536);
    SendMessage(Handle, WM_LBUTTONUP, 0, 159 + 350 * 65536);
    StartTime = GetTickCount();
    printf(">");
  }
  GetRGB(163, 314);
  if(Red == 239 && Green == 112 && Blue == 192){
    SendMessage(Handle, WM_LBUTTONDOWN, MK_LBUTTON, 163 + 314 * 65536);
    SendMessage(Handle, WM_LBUTTONUP, 0, 163 + 314 * 65536);
    StartTime = GetTickCount();
    printf(">");
  }
}

int GetStatus(void){
  int ret = 1;
  int i, j;
  ret = 0;
  for(j = 0; j < 8; j++){
    for(i = 0; i < 8; i++){
      Type[i][j] = GetColor(i, j);
    }
  }
  Sleep(DelayTime);
  for(j = 0; j < 8; j++){
    for(i = 0; i < 8; i++){
      if(Type[i][j] != GetColor(i, j)){
        ret++;
        Type[i][j] = 0;
      }
    }
  }
  return ret;
}


struct MoveQueue{
  int SrcX, SrcY, DstX, DstY;
} Queue[64], Result[64];
int History[65536][8][8][8][8];
int QueueIndex = 0, ResultIndex = 0, HistoryIndex = 0;
int BestAllCount1 = 0, BestAllCount2 = 0, BestCount5 = 0, BestCount4 = 0, BestCount3 = 0, BestCrossCount = 0;

void DequeueMessage(void){
  int Index = 0;
  for(Index = 0; Index < ResultIndex; Index++){
    if(Result[Index].SrcX == Result[Index].DstX){
      int x = 168 + Result[Index].SrcX * 40 + 20;
      int y0 = 30 + Result[Index].SrcY * 40 + 20;
      int y2 = 30 + Result[Index].DstY * 40 + 20;
      int y1 = (y0 + y2) / 2;
      SendNotifyMessage(Handle, WM_LBUTTONDOWN, MK_LBUTTON, x + y0 * 65536);
      SendNotifyMessage(Handle, WM_MOUSEMOVE, 0, x + y1 * 65536);
      SendNotifyMessage(Handle, WM_LBUTTONUP, 0, x + y2 * 65536);
    }else if(Result[Index].SrcY == Result[Index].DstY){
      int x0 = 168 + Result[Index].SrcX * 40 + 20;
      int x2 = 168 + Result[Index].DstX * 40 + 20;
      int x1 = (x0 + x2) / 2;
      int y = 30 + Result[Index].SrcY * 40 + 20;
      SendNotifyMessage(Handle, WM_LBUTTONDOWN, MK_LBUTTON, x0 + y * 65536);
      SendNotifyMessage(Handle, WM_MOUSEMOVE, 0, x1 + y * 65536);
      SendNotifyMessage(Handle, WM_LBUTTONUP, 0, x2 + y * 65536);
    }
  }
  ResultIndex = 0;
  HistoryIndex = 0;
  BestAllCount1 = 0;
  BestAllCount2 = 0;
  BestCount5 = 0;
  BestCount4 = 0;
  BestCount3 = 0;
  BestCrossCount = 0;
}

  int EnqueueMessage(int SrcX, int SrcY, int DstX, int DstY){
    if(Mark[SrcX][SrcY])
      return 0;

    if(Mark[DstX][DstY])
      return 0;

    if(Type[SrcX][SrcY] == Type[DstX][DstY])
      return 0;

    Mark[SrcX][SrcY] = 1;
    Mark[DstX][DstY] = 1;

    int Temp = Type[SrcX][SrcY];
    Type[SrcX][SrcY] = Type[DstX][DstY];
    Type[DstX][DstY] = Temp;

    if(SrcX < DstX || SrcY < DstY){
      Temp = SrcX;
      SrcX = DstX;
      DstX = Temp;
      Temp = SrcY;
      SrcY = DstY;
      DstY = Temp;
    }

    Queue[QueueIndex].SrcX = SrcX;
    Queue[QueueIndex].SrcY = SrcY;
    Queue[QueueIndex].DstX = DstX;
    Queue[QueueIndex].DstY = DstY;
    QueueIndex++;

    return 1;
  }

struct TempImage{
  struct MoveQueue Queue[64];
  int QueueIndex;
  int Type[8][8];
  int Mark[8][8];
} Image[64];
int AllCount1 = 0, AllCount2 = 0, Count5 = 0, Count4 = 0, Count3 = 0, CrossCount = 0;

  int Equal(int x1, int y1, int x2, int y2){
    if(x1 > 7 || x1 < 0 || y1 > 7 || y1 < 0 || x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0)
      return 0;

    if(Type[x1][y1] == 0 || Type[x2][y2] == 0)
      return 0;

    if(Type[x1][y1] != Type[x2][y2])
      return 0;

    return 1;
  }

  int NotEqual(int x1, int y1, int x2, int y2){
    if(x1 > 7 || x1 < 0 || y1 > 7 || y1 < 0 || x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0)
      return 0;

    if(Type[x1][y1] == 0 || Type[x2][y2] == 0 || Type[x1][y1] == 8 || Type[x2][y2] == 8)
      return 0;

    if(Type[x1][y1] == Type[x2][y2])
      return 0;

    return 1;
  }


void SaveImage(int Step){
  int i, j;
  for(i = 0; i < 8; i++)
    for(j = 0; j < 8; j++){
      Image[Step].Type[i][j] = Type[i][j];
      Image[Step].Mark[i][j] = Mark[i][j];
    }
  for(i = 0; i < QueueIndex; i++)
    Image[Step].Queue[i] = Queue[i];
  Image[Step].QueueIndex = QueueIndex;
}

void LoadImage(int Step){
  int i, j;
  for(i = 0; i < 8; i++)
    for(j = 0; j < 8; j++){
      Type[i][j] = Image[Step].Type[i][j];
      Mark[i][j] = Image[Step].Mark[i][j];
    }
  for(i = 0; i < Image[Step].QueueIndex; i++)
    Queue[i] = Image[Step].Queue[i];
  QueueIndex = Image[Step].QueueIndex;
}

int FindAllConnect1(int Step){
  int i, j, ret = 0;

  for(i = 7; i >= 0; i--)
    for(j = 7; j >= 0; j--)
      if(Type[i][j] == 8){
        if(Equal(i, j, i + 1, j) || Type[i + 1][j] == 0){
          SaveImage(Step);
          if(EnqueueMessage(i, j, i + 1, j)){
            AllCount1++;
            FindMove(Step + 1);
            AllCount1--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i, j + 1) || Type[i][j + 1] == 0){
          SaveImage(Step);
          if(EnqueueMessage(i, j, i, j + 1)){
            AllCount1++;
            FindMove(Step + 1);
            AllCount1--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i - 1, j) || Type[i - 1][j] == 0){
          SaveImage(Step);
          if(EnqueueMessage(i, j, i - 1, j)){
            AllCount1++;
            FindMove(Step + 1);
            AllCount1--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i, j - 1) || Type[i][j - 1] == 0){
          SaveImage(Step);
          if(EnqueueMessage(i, j, i, j - 1)){
            AllCount1++;
            FindMove(Step + 1);
            AllCount1--;
          }
          LoadImage(Step);
        }

      }

  return ret;
}

int FindAllConnect2(int Step){
  int i, j, k, l, ret = 0;

  for(i = 7; i >= 0; i--)
    for(j = 7; j >= 0; j--)
      if(Type[i][j] == 8){
        if(j < 7 && Type[i][j + 1] == 0)
          continue;
        if(j > 0 && Type[i][j - 1] == 0)
          continue;
        if(i < 7 && Type[i + 1][j] == 0)
          continue;
        if(i > 0 && Type[i - 1][j] == 0)
          continue;

        int C1 = 0, C2 = 0, C3 = 0, C4 = 0;
        for(k = 0; k < 8; k++)
          for(l = 0; l < 8; l++){
            if(Equal(i, j + 1, k, l))
              C1++;
            if(Equal(i, j - 1, k, l))
              C2++;
            if(Equal(i + 1, j, k, l))
              C3++;
            if(Equal(i - 1, j, k, l))
              C4++;
          }

        if(C1 >= C2 && C1 >= C3 && C1 >= C4 && Type[i][j + 1] != 0){
          SaveImage(Step);
          if(EnqueueMessage(i, j, i, j + 1)){
            for(k = 0; k < 8; k++)
              for(l = 0; l < 8; l++)
                if(Equal(i, j, k, l))
                  Type[k][l] = 0;
            AllCount2++;
            FindMove(Step + 1);
            AllCount2--;
          }
          LoadImage(Step);
        }
        if(C2 >= C1 && C2 >= C3 && C2 >= C4 && Type[i][j - 1] != 0){
          SaveImage(Step);
          if(EnqueueMessage(i, j, i, j - 1)){
            for(k = 0; k < 8; k++)
              for(l = 0; l < 8; l++)
                if(Equal(i, j, k, l))
                  Type[k][l] = 0;
            AllCount2++;
            FindMove(Step + 1);
            AllCount2--;
          }
          LoadImage(Step);
        }
        if(C3 >= C1 && C3 >= C2 && C3 >= C4 && Type[i + 1][j] != 0){
          SaveImage(Step);
          if(EnqueueMessage(i, j, i + 1, j)){
            for(k = 0; k < 8; k++)
              for(l = 0; l < 8; l++)
                if(Equal(i, j, k, l))
                  Type[k][l] = 0;
            AllCount2++;
            FindMove(Step + 1);
            AllCount2--;
          }
          LoadImage(Step);
        }
        if(C4 >= C1 && C4 >= C2 && C4 >= C4 && Type[i - 1][j] != 0){
          SaveImage(Step);
          if(EnqueueMessage(i, j, i - 1, j)){
            for(k = 0; k < 8; k++)
              for(l = 0; l < 8; l++)
                if(Equal(i, j, k, l))
                  Type[k][l] = 0;
            AllCount2++;
            FindMove(Step + 1);
            AllCount2--;
          }
          LoadImage(Step);
        }
      }

  return ret;
}

int Find5Connect(int Step){
  int i, j, k, ret = 0;

  for(i = 7; i >= 0; i--)
    for(j = 7; j >= 0; j--){
      if(Equal(i, j, i, j + 1) && Equal(i, j, i, j + 3) && Equal(i, j, i, j + 4) && NotEqual(i, j, i, j + 2)){
        if(Equal(i, j, i + 1, j + 2)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j + 2, i, j + 2)){
            for(k = 0; k < 5; k++)
              Mark[i][j + k] = 1;
            Count5++;
            FindMove(Step + 1);
            Count5--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i - 1, j + 2)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j + 2, i, j + 2)){
            for(k = 0; k < 5; k++)
              Mark[i][j + k] = 1;
            Count5++;
            FindMove(Step + 1);
            Count5--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j, i + 1, j) && Equal(i, j, i + 3, j) && Equal(i, j, i + 4, j) && NotEqual(i, j, i + 2, j)){
        if(Equal(i, j, i + 2, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 2, j + 1, i + 2, j)){
            for(k = 0; k < 5; k++)
              Mark[i + k][j] = 1;
            Count5++;
            FindMove(Step + 1);
            Count5--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i + 2, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 2, j - 1, i + 2, j)){
            for(k = 0; k < 5; k++)
              Mark[i + k][j] = 1;
            Count5++;
            FindMove(Step + 1);
            Count5--;
          }
          LoadImage(Step);
        }
      }
    }

  return ret;
}

int FindCrossConnect(int Step){
  int i, j, k, ret = 0;

  for(i = 7; i >= 0; i--)
    for(j = 7; j >= 0; j--){
      if(Equal(i, j + 1, i, j + 2) && Equal(i + 1, j, i + 2, j) && Equal(i + 1, j, i, j + 1) && NotEqual(i, j, i, j + 1)){
        if(Equal(i, j + 1, i - 1, j)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j, i, j)){
            for(k = 1; k < 3; k++){
              Mark[i + k][j] = 1;
              Mark[i][j + k] = 1;
            }
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j + 1, i, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i, j - 1, i, j)){
            for(k = 1; k < 3; k++){
              Mark[i + k][j] = 1;
              Mark[i][j + k] = 1;
            }
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j + 1, i, j + 2) && Equal(i - 1, j, i - 2, j) && Equal(i - 1, j, i, j + 1) && NotEqual(i, j, i, j + 1)){
        if(Equal(i, j + 1, i + 1, j)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j, i, j)){
            for(k = 1; k < 3; k++){
              Mark[i - k][j] = 1;
              Mark[i][j + k] = 1;
            }
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j + 1, i, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i, j - 1, i, j)){
            for(k = 1; k < 3; k++){
              Mark[i - k][j] = 1;
              Mark[i][j + k] = 1;
            }
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j - 1, i, j - 2) && Equal(i - 1, j, i - 2, j) && Equal(i - 1, j, i, j - 1) && NotEqual(i, j, i, j - 1)){
        if(Equal(i, j - 1, i + 1, j)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j, i, j)){
            for(k = 1; k < 3; k++){
              Mark[i - k][j] = 1;
              Mark[i][j - k] = 1;
            }
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j - 1, i, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i, j + 1, i, j)){
            for(k = 1; k < 3; k++){
              Mark[i - k][j] = 1;
              Mark[i][j - k] = 1;
            }
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j - 1, i, j - 2) && Equal(i + 1, j, i + 2, j) && Equal(i + 1, j, i, j - 1) && NotEqual(i, j, i, j - 1)){
        if(Equal(i, j - 1, i - 1, j)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j, i, j)){
            for(k = 1; k < 3; k++){
              Mark[i + k][j] = 1;
              Mark[i][j - k] = 1;
            }
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j - 1, i, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i, j + 1, i, j)){
            for(k = 1; k < 3; k++){
              Mark[i + k][j] = 1;
              Mark[i][j - k] = 1;
            }
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j - 1, i, j + 1) && Equal(i + 1, j, i + 2, j) && Equal(i, j - 1, i + 1, j) && NotEqual(i, j, i, j - 1)){
        if(Equal(i - 1, j, i + 1, j)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j, i, j)){
            Mark[i][j - 1] = 1;
            Mark[i][j + 1] = 1;
            Mark[i + 1][j] = 1;
            Mark[i + 2][j] = 1;
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j - 1, i, j + 1) && Equal(i - 1, j, i - 2, j) && Equal(i, j - 1, i - 1, j) && NotEqual(i, j, i, j - 1)){
        if(Equal(i + 1, j, i - 1, j)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j, i, j)){
            Mark[i][j - 1] = 1;
            Mark[i][j + 1] = 1;
            Mark[i - 1][j] = 1;
            Mark[i - 2][j] = 1;
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i + 1, j, i - 1, j) && Equal(i, j + 1, i, j + 2) && Equal(i + 1, j, i, j + 1) && NotEqual(i, j, i + 1, j)){
        if(Equal(i, j - 1, i, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i, j - 1, i, j)){
            Mark[i + 1][j] = 1;
            Mark[i - 1][j] = 1;
            Mark[i][j + 1] = 1;
            Mark[i][j + 2] = 1;
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i + 1, j, i - 1, j) && Equal(i, j - 1, i, j - 2) && Equal(i + 1, j, i, j - 1) && NotEqual(i, j, i + 1, j)){
        if(Equal(i, j + 1, i, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i, j + 1, i, j)){
            Mark[i + 1][j] = 1;
            Mark[i - 1][j] = 1;
            Mark[i][j - 1] = 1;
            Mark[i][j - 2] = 1;
            CrossCount++;
            FindMove(Step + 1);
            CrossCount--;
          }
          LoadImage(Step);
        }
      }
    }

  return ret;
}


int Find4Connect(int Step){
  int i, j, k, ret = 0;

  for(i = 7; i >= 0; i--)
    for(j = 7; j >= 0; j--){
      if(Equal(i, j, i, j + 1) && Equal(i, j, i, j + 3) && NotEqual(i, j, i, j + 2)){
        if(Equal(i, j, i + 1, j + 2)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j + 2, i, j + 2)){
            for(k = 0; k < 4; k++)
              Mark[i][j + k] = 1;
            Count4++;
            FindMove(Step + 1);
            Count4--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i - 1, j + 2)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j + 2, i, j + 2)){
            for(k = 0; k < 4; k++)
              Mark[i][j + k] = 1;
            Count4++;
            FindMove(Step + 1);
            Count4--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j, i + 1, j) && Equal(i, j, i + 3, j) && NotEqual(i, j, i + 2, j)){
        if(Equal(i, j, i + 2, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 2, j + 1, i + 2, j)){
            for(k = 0; k < 4; k++)
              Mark[i + k][j] = 1;
            Count4++;
            FindMove(Step + 1);
            Count4--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i + 2, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 2, j - 1, i + 2, j)){
            for(k = 0; k < 4; k++)
              Mark[i + k][j] = 1;
            Count4++;
            FindMove(Step + 1);
            Count4--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j, i, j + 2) && Equal(i, j, i, j + 3) && NotEqual(i, j, i, j + 1)){
        if(Equal(i, j, i + 1, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j + 1, i, j + 1)){
            for(k = 0; k < 4; k++)
              Mark[i][j + k] = 1;
            Count4++;
            FindMove(Step + 1);
            Count4--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i - 1, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j + 1, i, j + 1)){
            for(k = 0; k < 4; k++)
              Mark[i][j + k] = 1;
            Count4++;
            FindMove(Step + 1);
            Count4--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j, i + 2, j) && Equal(i, j, i + 3, j) && NotEqual(i, j, i + 1, j)){
        if(Equal(i, j, i + 1, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j + 1, i + 1, j)){
            for(k = 0; k < 4; k++)
              Mark[i + k][j] = 1;
            Count4++;
            FindMove(Step + 1);
            Count4--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i + 1, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j - 1, i + 1, j)){
            for(k = 0; k < 4; k++)
              Mark[i + k][j] = 1;
            Count4++;
            FindMove(Step + 1);
            Count4--;
          }
          LoadImage(Step);
        }
      }
    }

  return ret;		
}

int Find3Connect(int Step){
  int i, j, k, ret = 0;

  for(i = 7; i >= 0; i--)
    for(j = 7; j >= 0; j--){
      if(Equal(i, j, i, j + 1) && NotEqual(i, j, i, j + 2)){
        if(Equal(i, j, i + 1, j + 2)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j + 2, i, j + 2)){
            for(k = 0; k < 3; k++)
              Mark[i][j + k] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i - 1, j + 2)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j + 2, i, j + 2)){
            for(k = 0; k < 3; k++)
              Mark[i][j + k] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i, j + 3)){
          SaveImage(Step);
          if(EnqueueMessage(i, j + 3, i, j + 2)){
            for(k = 0; k < 3; k++)
              Mark[i][j + k] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j, i + 1, j) && NotEqual(i, j, i + 2, j)){
        if(Equal(i, j, i + 2, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 2, j + 1, i + 2, j)){
            for(k = 0; k < 3; k++)
              Mark[i + k][j] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i + 2, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 2, j - 1, i + 2, j)){
            for(k = 0; k < 3; k++)
              Mark[i + k][j] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i + 3, j)){
          SaveImage(Step);
          if(EnqueueMessage(i + 3, j, i + 2, j)){
            for(k = 0; k < 3; k++)
              Mark[i + k][j] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j, i, j + 2) && NotEqual(i, j, i, j + 1)){
        if(Equal(i, j, i + 1, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j + 1, i, j + 1)){
            for(k = 0; k < 3; k++)
              Mark[i][j + k] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i - 1, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j + 1, i, j + 1)){
            for(k = 0; k < 3; k++)
              Mark[i][j + k] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j, i + 2, j) && NotEqual(i, j, i + 1, j)){
        if(Equal(i, j, i + 1, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j + 1, i + 1, j)){
            for(k = 0; k < 3; k++)
              Mark[i + k][j] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j, i + 1, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j - 1, i + 1, j)){
            for(k = 0; k < 3; k++)
              Mark[i + k][j] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i, j + 1, i, j + 2) && NotEqual(i, j, i, j + 1)){
        if(Equal(i, j + 1, i + 1, j)){
          SaveImage(Step);
          if(EnqueueMessage(i + 1, j, i, j)){
            for(k = 0; k < 3; k++)
              Mark[i][j + k] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j + 1, i - 1, j)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j, i, j)){
            for(k = 0; k < 3; k++)
              Mark[i][j + k] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i, j + 1, i, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i, j - 1, i, j)){
            for(k = 0; k < 3; k++)
              Mark[i][j + k] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
      }
      if(Equal(i + 1, j, i + 2, j) && NotEqual(i, j, i + 1, j)){
        if(Equal(i + 1, j, i, j + 1)){
          SaveImage(Step);
          if(EnqueueMessage(i, j + 1, i, j)){
            for(k = 0; k < 3; k++)
              Mark[i + k][j] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i + 1, j, i, j - 1)){
          SaveImage(Step);
          if(EnqueueMessage(i, j - 1, i, j)){
            for(k = 0; k < 3; k++)
              Mark[i + k][j] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
        if(Equal(i + 1, j, i - 1, j)){
          SaveImage(Step);
          if(EnqueueMessage(i - 1, j, i, j)){
            for(k = 0; k < 3; k++)
              Mark[i + k][j] = 1;
            Count3++;
            FindMove(Step + 1);
            Count3--;
          }
          LoadImage(Step);
        }
      }
    }

  return ret;
}

int CheckHistory(void){
  int Index, i, j, k, l;

  for(Index = HistoryIndex - 1; Index >= 0; Index--){
    int NotInclude = 0;
    for(i = 0; i < QueueIndex; i++)
      if(History[Index][Queue[i].SrcX][Queue[i].SrcY][Queue[i].DstX][Queue[i].DstY] == 0){
        NotInclude = 1;
        break;
      }
    if(NotInclude == 0)
      return 1;
  }

  for(i = 0; i < 8; i++)
    for(j = 0; j < 8; j++)
      for(k = 0; k < 8; k++)
        for(l = 0; l < 8; l++)
          History[HistoryIndex][i][j][k][l] = 0;

  for(Index = 0; Index < QueueIndex; Index++)
    History[HistoryIndex][Queue[Index].SrcX][Queue[Index].SrcY][Queue[Index].DstX][Queue[Index].DstY] = 1;
  HistoryIndex++;
  return 0;
}


int FindMove(int Step){
  int ret = 0, i;
  if(AllCount1){
    BestAllCount1 = AllCount1;
    BestAllCount2 = AllCount2;
    BestCount5 = Count5;
    BestCount4 = Count4;
    BestCount3 = Count3;
    BestCrossCount = CrossCount;
    for(i = 0; i < QueueIndex; i++)
      Result[i] = Queue[i];
    ResultIndex = QueueIndex;
    return 1;
  }
  if(AllCount2){
    BestAllCount1 = AllCount1;
    BestAllCount2 = AllCount2;
    BestCount5 = Count5;
    BestCount4 = Count4;
    BestCount3 = Count3;
    BestCrossCount = CrossCount;
    for(i = 0; i < QueueIndex; i++)
      Result[i] = Queue[i];
    ResultIndex = QueueIndex;
    return 1;
  }

  if(CheckHistory())
    return 0;
  ret += FindAllConnect1(Step);
  ret += FindAllConnect2(Step);
  ret += Find5Connect(Step);
  ret += FindCrossConnect(Step);
  ret += Find4Connect(Step);
  ret += Find3Connect(Step);
  if(AllCount1 > BestAllCount1 || 
      (AllCount1 == BestAllCount1 && Count5 > BestCount5) || 
      (AllCount1 == BestAllCount1 && Count5 == BestCount5 && CrossCount > BestCrossCount) || 
      (AllCount1 == BestAllCount1 && Count5 == BestCount5 && CrossCount == BestCrossCount && Count4 > BestCount4) || 
      (AllCount1 == BestAllCount1 && Count5 == BestCount5 && CrossCount == BestCrossCount && Count4 == BestCount4 && Count3 > BestCount3)){
    BestAllCount1 = AllCount1;
    BestAllCount2 = AllCount2;
    BestCount5 = Count5;
    BestCount4 = Count4;
    BestCount3 = Count3;
    BestCrossCount = CrossCount;
    for(i = 0; i < QueueIndex; i++)
      Result[i] = Queue[i];
    ResultIndex = QueueIndex;
  }
  return 1;
}

int main()
{
  int nRetCode = 0;

  printf("寶石方塊機器人，由 Sitos Lin (sitos.lin@gmail.com) 製作。\n適用 chrome 及 firefox ，建議以雙核心以上機種執行。\n\n");

  printf("請輸入等待盤面穩定時間 (ms)，數值越高誤判越少，但移動越慢，建議數值為 20~80:");
  scanf("%d", &DelayTime);

  while(1){
    printf("試圖取得 Handle\n");
    while(IsWindow(Handle) == FALSE){
      FindHandle();
      Sleep(500);
    }

    // 初始化 MFC 並於失敗時列印錯誤
    if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
      // TODO: 配合您的需要變更錯誤碼
      _tprintf(_T("嚴重錯誤: MFC 初始化失敗\n"));
      nRetCode = 1;
    }
    else
    {
      // TODO: 在此撰寫應用程式行為的程式碼。
      Browser = GetDC((HWND)Handle);

      int Change = 0;
      while(1){
        ChooseItem();
        Change = GetStatus();
        printf("|");
        if(Change < 1){
          printf("?");
          FindMove(0);
          printf("=");
          DequeueMessage();
        }
        if(IsWindow(Handle) == FALSE)
          break;

      }

    }
  }

}
