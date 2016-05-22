#include"io.h"
#include<algorithm>
using namespace std;
const int H = 256, W = 256;
unsigned char s[H][W];
main() {
  int i, j, lb, ub;
  LoadImage(H*W, s);
  lb = ub = s[0][0];
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j) {
      if (s[i][j] < lb) lb = s[i][j];
      if (s[i][j] > ub) ub = s[i][j];
    }
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      s[i][j] = (s[i][j] - lb)*256/(ub - lb);
  SaveImage(H*W, s);
}
