#include"io.h"
#include<cmath>
#include<cstdio>
const int H = 128, W = 640;
const double u0 = 1e-6;
inline double abs(double x) {
  return x < 0? -x: x;
}
bool mod(int& x, int& y) {
  double nx = x - 63.5, ny = y;
  if (abs(nx) >= 64 - y/2) return false;
  nx *= 64/(64 - y/2);
  x = nx + 64;
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
      if (mod(x, y)) {
        t[i][j+128] = s[x][y+128];
        t[i][511-j] = s[x][511-j];
      }
      else t[i][j+128] = t[i][511-j] = 255;
    }
  SaveImage(H*W, t);
}
