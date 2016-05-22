#include"io.h"
#include<cmath>
#include<cstdio>
const int H = 256, W = 256;
const double u0 = 1e-6;
unsigned char s[H][W], t[H][W];
int r[12];
void rotate(int &x, int& y, int r) {
  const double pi = acos(-1);
  double nx = x - 127.5, ny = y - 127.5;
  double l = sqrt(nx*nx + ny*ny);
  double t = acos(ny/l);
  nx = l*sin(t + r*pi/180);
  ny = l*cos(t + r*pi/180);
  x = nx + 127.5;
  y = ny + 127.5;
}
bool match(int x, int y, int r) {
  double nx = x - 127.5, ny = y - 127.5;
  double l = sqrt(nx*nx + ny*ny);
  return fabs(r - l) < 2;
}
main() {
  LoadImage(H*W, s);
  int i ,j, k;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      t[i][j] = s[i][j];
  for (i = 0; i < 11; ++i)
    r[i] = (1 + i)*11;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j) {
      for (k = 0; k < 12; ++k) {
        if (!match(i, j, r[k])) continue;
        int x = i, y = j;
        rotate(x, y, r[k]);
        t[i][j] = s[x][y];
      }
    }
  SaveImage(H*W, t);
}
