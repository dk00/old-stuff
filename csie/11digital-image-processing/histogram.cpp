#include"io.h"
const int H = 512, W = 512;
unsigned char s[H][W], t[H][W];
unsigned count[256];
int main() {
  int i, j, k, sx, sy, ub;
  LoadImage(H*W, s);
  for (k = 0; k < 4; ++k) {
    sx = k/2*256;
    sy = k%2*256;
    for (i = 0; i < 256; ++i) count[i] = 0;
    for (i = 0; i < H/2; ++i)
      for (j = 0; j < W/2; ++j)
        if (++count[s[sx+i][sy+j]] > ub)
          ub = count[s[sx+i][sy+j]];
    for (i = 0; i < H/2; ++i)
      for (j = 0; j < W/2; ++j)
        t[sx+i][sy+j] = 255*(256*count[j]/ub <= 255 - i);
  }
  SaveImage(H*W, t);
}

