#include<cstdio>
#include"blitz.h"
#include"Color.h"
unsigned c[BoardH][BoardW];
int type[BoardH][BoardW];
void Conv(unsigned c[BoardH][BoardW]) {
  int i, j, k, r, g, b;
  for (i = 0; i < BoardH; ++i)
    for (j = 0; j < BoardW; ++j) {
      k = c[i][j];
      if (Color[k] >= 0) {
        c[i][j] = Color[k];
        continue;
      }
      if (r < 10 && g < 10 && b < 10) {
        c[i][j] = 0;
        continue;
      }
      r = (k>>8)&15;
      g = (k>>4)&15;
      b = k&15;
      c[i][j] = ((r>7)<<2)|((g>7)<<1)|(b>7);
    }
}
#include<ctime>
main() {
  FindGameWindow();
  Dirc move[256];
  for (int i = 0; i < 256; ++i)
    move[i] = X;
  move['u'] = move['U'] = U;
  move['l'] = move['L'] = L;
  move['d'] = move['D'] = D;
  move['r'] = move['R'] = R;
  char cmd[99];
  SetColor();
  printf("%d\n", Color[0xB73]);
  while (scanf("%s", cmd) == 1) {
    if (move[cmd[0]] != X) {
      int x, y;
      scanf("%d %d", &x, &y);
      SendMove(x, y, move[cmd[0]]);
      continue;
    }
    GetBoard(c);
//    Conv(c);
    int i, j, k;
    char name[]="bBGyRPYWO";
    for (i = 0; i < 8; ++i, puts(""))
      for (j = 0; j < 8; ++j) {
        printf("%03X ", c[i][j]);
//        printf("%c ", name[c[i][j]]);
      }
  }
}
