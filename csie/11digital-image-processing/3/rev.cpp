#include"io.h"
using namespace std;
const int H = 256, W = 256;
unsigned char s[H][W];
main() {
  LoadImage(H*W, s);
  int i, j, k;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
        s[i][j] = 255 - s[i][j];
  SaveImage(H*W, s);
}
