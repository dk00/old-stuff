#include"io.h"
#include<cmath>
#include<cstdio>
const int H = 128, W = 640;
const double u0 = 1e-6;
inline double abs(double x) {
  return x < 0? -x: x;
}
bool mod(int& x, int& y) {
  double nx = x - 31.5, ny = 127 - y;
  nx *= 2;
  double l = sqrt(nx*nx + ny*ny);
  if (l >= 64) return false;
  if (abs(nx) < abs(ny)) nx *= l/abs(ny), ny = l;
  else ny *= l/abs(nx), nx = l;
  nx /= 2;
  x = nx + 31.5;
  y = 127 - ny;
  return true;
}
unsigned char s[H][W], t[H][W];
main() {
  LoadImage(H*W, s);
  int i ,j;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      t[i][j] = s[i][j];
  for (i = 0; i < 64; ++i)
    for (j = 0; j < 128; ++j) {
      int x = i, y = j;
      if (mod(x, y)) {
        t[i][j] = s[x][y];
        t[i+64][j] = s[x+64][y];
        t[i][639-j] = s[x][639-y];
        t[i+64][639-j] = s[x+64][639-y];
      }
      else t[i][j] = t[i+64][j] = t[i][639-j] = t[i+64][639-j] =255;
    }
  SaveImage(H*W, t);
}
