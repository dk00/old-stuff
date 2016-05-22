#include"io.h"
#include<algorithm>
using namespace std;
const int H = 256, W = 256;
struct pt {
  int x, y, c;
  bool operator <(pt a) const {
    return c < a.c;
  }
} t[H*W];
unsigned char s[H][W];
unsigned count[256];
unsigned m;
main() {
  int i, j;
  LoadImage(H*W, s);
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j) {
      unsigned k = s[i][j]/51*64;
      if (k > 255) k = 255;
      s[i][j] = k;
    }
  SaveImage(H*W, s);
}
