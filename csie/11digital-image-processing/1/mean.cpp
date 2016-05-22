#include"io.h"
#include<algorithm>
using namespace std;
const int H = 256, W = 256, dx[] = {1, 1, 1, 0, 0, 0, -1, -1, -1}, 
      dy[] = {1, 0, -1, 1, 0, -1, 1, 0, -1},
      w[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
unsigned char s[H][W], t[H][W];
unsigned BoxMean(unsigned char s[H][W], int x, int y) {
  unsigned i, j, m, tmp;
  for (m = tmp = 0, i = 0; i < 9; ++i)
    if (x+dx[i] >= 0 && x+dx[i] < H && y+dy[i] >= 0 && y+dy[i] < W) {
      m += w[i];
      tmp += s[x+dx[i]][y+dy[i]]*w[i];
    }
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
