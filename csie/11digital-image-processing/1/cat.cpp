#include"io.h"
const int H = 512, W = 512;
unsigned char s[H/2][W/2], t[H][W];
int main(int argc, char **argv) {
  int i, j, k, sx, sy;
  if (argc < 5) return 0;
  for (k = 1; k < 5; ++k) {
    freopen(argv[k], "rb", stdin);
    LoadImage(H*W/4, s);
    sx = (k-1)/2*256;
    sy = (k-1)%2*256;
    for (i = 0; i < H/2; ++i)
      for (j = 0; j < W/2; ++j)
        t[sx+i][sy+j] = s[i][j];
  }
  SaveImage(H*W, t);
}

