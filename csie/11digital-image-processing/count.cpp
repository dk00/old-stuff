#include"io.h"
const int H = 256, W = 256;
unsigned char s[H][W];
unsigned count[256];
main() {
  int i, j;
  LoadImage(H*W, s);
  for (i = 0; i < 256; ++i)
    count[i] = 0;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      ++count[s[i][j]];
  for (i = 0; i < 16; ++i, puts(""))
    for (j = 0; j < 16; ++j)
      printf("%3d ", count[i*16+j]);
}
