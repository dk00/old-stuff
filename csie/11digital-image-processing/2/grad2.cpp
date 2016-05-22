#include"io.h"
#include<algorithm>
using namespace std;
const int H = 256, W = 256, dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1}, 
      dy[] = {1, 0, -1, 1, 0, -1, 1, 0, -1},
      w[] = {1, 1, 1, 1, -8, 1, 1, 1, 1};
unsigned char s[H][W];
int t[H][W];
int mag(unsigned char s[H][W], int x, int y) {
  unsigned i, j;
  int  nx, ny, u = 0, m = 0;
  for (i = 0; i < 9; ++i) {
    nx = x + dx[i], ny = y + dy[i];
    if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
    u += s[nx][ny]*w[i];
    ++m;
  }
  return u;
}
int lb, ub, Count[256];
inline int Rank(int x) {
  return Count[255*(x-lb)/(ub-lb)];
}
int cross(int s[H][W], int x, int y) {
  unsigned i, j;
  int  nx, ny, u = 0, v = 0;
  for (i = 0; i < 4; ++i) {
    nx = x + dx[i], ny = y + dy[i];
    if (nx < 0 || nx >= H || ny < 0 || ny >= W) return 0;
    u = s[nx][ny];
    nx = x + dx[i], ny = y + dy[i];
    if (nx < 0 || nx >= H || ny < 0 || ny >= W) return 0;
    v = s[nx][ny];
    if (Rank(u) <= 100 && Rank(v) <= 100 && Rank(s[x][y]) > 100) return 1;
  }
  
  return 0;
}
main() {
  int i, j;
  LoadImage(H*W, s);
  lb = 200000;
  ub = -lb;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j) {
      t[i][j] = mag(s, i, j);
      if (t[i][j] < lb) lb = t[i][j];
      if (t[i][j] > ub) ub = t[i][j];
    }
  fprintf(stderr, "%d %d\n", lb, ub);
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      ++Count[255*(t[i][j]-lb)/(ub-lb)];
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      if (cross(t, i, j)) s[i][j] = 0;
      else s[i][j] = 255;
  SaveImage(H*W, s);
}
