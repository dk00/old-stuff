#include"io.h"
const int H = 256, W = 256;
unsigned char s[H][W], t[H][W];
int main(int argc, char **argv) {
  int i, j;
  if (argc < 3) return 0;
  freopen(argv[1], "rb", stdin);
  LoadImage(H*W, s);
  freopen(argv[2], "rb", stdin);
  LoadImage(H*W, t);
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      t[i][j] = ~((~t[i][j]) | ~s[i][j]);
  SaveImage(H*W, t);
}

