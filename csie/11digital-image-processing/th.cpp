#include"io.h"
#include<algorithm>
using namespace std;
const int H = 256, W = 256, dx[] = {-1, 0, 1, -1, -1, 0, 1, 1}, 
      dy[] = {-1, -1, -1, 0, 1, 1, 1, 0},
      w[] = {-1, -1, -1, -1, 9, -1, -1, -1, -1};
unsigned char s[H][W], t[H][W];
unsigned g(unsigned char s[H][W], int x, int y) {
  unsigned i, j;
  int  nx, ny, m = 0;
  for (i = 0; i < 8; ++i) {
    nx = x + dx[i], ny = y + dy[i];
    if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
    if (s[nx][ny] > 64) ++m;
  }
  if (m > 2) m = s[x][y] + 24;
  else m = s[x][y]*2/5;
  return m;
}
int Count[256];
main() {
  int i, j;
  LoadImage(H*W, s);
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      t[i][j] = g(s, i, j);
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      t[i][j] = 255 - (t[i][j] > 64)*255;
  SaveImage(H*W, t);
}
