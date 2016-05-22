#include"io.h"
#include<cmath>
#include<cstdio>
const int H = 128, W = 640;
const double u0 = 1e-6;
inline double abs(double x) {
  return x < 0? -x: x;
}
bool mod(int& x, int& y) {
  double nx = x - 63.5, ny = y - 63.5;
  double l = sqrt(nx*nx + ny*ny);
  if (l >= 64) return false;
  if (abs(nx) < abs(ny)) nx *= l/abs(ny), ny = l;
  else ny *= l/abs(nx), nx = l;
  x = nx + 64;
  y = ny + 64;
  return true;
}
unsigned char s[H][W], t[H][W];
main() {
  LoadImage(H*W, s);
  int i ,j;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      t[i][j] = s[i][j];
  for (i = 0; i < 128; ++i)
    for (j = 0; j < 128; ++j) {
      int x = i, y = j;
      if (mod(x, y))
        t[i][j+256] = s[x][y+256];
      else t[i][j+256] = 255;
    }
  SaveImage(H*W, t);
}
