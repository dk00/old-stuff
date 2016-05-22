#include"io.h"
#include<algorithm>
using namespace std;
const int H = 256, W = 256;
unsigned char s[H][W], t[H][W];
unsigned count[256];
unsigned BoxMid(unsigned char s[H][W], int x, int y) {
  int i, j, m, tmp[99];
  for (m = 0, i = -1; i <= 1; ++i)
    for (j = -1; j <= 1; ++j)
      if (x+i >= 0 && x+i < H && y+j >= 0 && y+j < W)
        tmp[m++] = s[x+i][y+j];
  sort(tmp, tmp+m);
  return tmp[m/2];
}
main() {
  int i, j;
  LoadImage(H*W, s);
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j) {
      t[i][j] = BoxMid(s, i, j);
    }
  SaveImage(H*W, t);
}
