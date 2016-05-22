#include"io.h"
#include<algorithm>
using namespace std;
const int H = 256, W = 256, dx[] = {1, 1, 1, 0, 0, 0, -1, -1, -1}, 
      dy[] = {1, 0, -1, 1, 0, -1, 1, 0, -1},
      w[] = {-8, -8, -8, -8, 78, -8, -8, -8, -8};
unsigned char s[H][W], t[H][W];
unsigned BoxMean(unsigned char s[H][W], int x, int y) {
  unsigned i, j, m;
  int tmp;
  for (tmp = i = m = 0; i < 9; ++i)
    if (x+dx[i] >= 0 && x+dx[i] < H && y+dy[i] >= 0 && y+dy[i] < W)
      m += w[i], tmp += s[x+dx[i]][y+dy[i]]*w[i];
  if (tmp < 0) tmp = 0;
  if (tmp / m > 255) tmp = 255*m;
  return tmp/m;
}
main() {
  int i, j;
  LoadImage(H*W, s);
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      t[i][j] = BoxMean(s, i, j);
  SaveImage(H*W, t);
}
