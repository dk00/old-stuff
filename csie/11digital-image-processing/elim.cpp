#include"io.h"
#include<cstdio>
const int H = 256, W = 256;
const double u0 = 1e-6;
inline double abs(double x) {return x < 0? -x: x;}
double s[9][9], 
  x[] = {255, 0, 0, 255, 64, 127},
  y[] = {0, 255, 0, 255, 127, 255},
  u[] = {255, 0, 0, 180.31222, 57.153, 113.6813},
  v[] = {0, 255, 0, 180.31222, 113.413, 228.2577};
int n = 6;
inline void swap(double a[], double b[]) {
  int i;
  double j;
  for (i = 0; i <= n; ++i)
    j = a[i], a[i] = b[i], b[i] = j;
}
inline void sub(double a[], double b[], double c) {
  for (int i = 0; i <= n; ++i)
    a[i] -= b[i] * c;
}
double a[9], b[9];
void mod(unsigned& x, unsigned& y) {
  double nx = x, ny = y;
  nx = a[0] + a[1]*x + a[2]*y + a[3]*x*x + a[4]*y*y + a[5]*x*y;
  ny = b[0] + b[1]*x + b[2]*y + b[3]*x*x + b[4]*y*y + b[5]*x*y;
  fprintf(stderr, "%u %u %lf %lf", x, y, nx, ny);
  if (nx < 0) nx = 0;
  if (ny < 0) ny = 0;
  x = (unsigned)nx, y = (unsigned)ny;
  fprintf(stderr, " %u %u\n", x, y);
}
unsigned char t[H][W];
main() {
  int i ,j;
  for (i = 0; i < n; ++i) {
    s[i][0] = 1;
    s[i][1] = x[i];
    s[i][2] = y[i];
    s[i][3] = x[i]*x[i];
    s[i][4] = y[i]*y[i];
    s[i][5] = x[i]*y[i];
    s[i][6] = u[i];
  }
  for (i = 0; i < n; ++i) {
    for (j = i; j < n; ++j)
      if (abs(s[j][i]) > u0) break;
    if (j >= n) break;
    if (i != j) swap(s[i], s[j]);
    for (j = 0; j < n; ++j)
      if (i != j) sub(s[j], s[i], s[j][i]/s[i][i]);
  }
  for (i = 0; i < n; ++i, fprintf(stderr, "\n"))
    for (j = 0; j <= n; ++j)
      fprintf(stderr, "%lf ", s[i][j]);
  for (i = 0; i < n; ++i)
    a[i] = s[i][n]/s[i][i];
  for (i = 0; i < n; ++i) {
    s[i][0] = 1;
    s[i][1] = x[i];
    s[i][2] = y[i];
    s[i][3] = x[i]*x[i];
    s[i][4] = y[i]*y[i];
    s[i][5] = x[i]*y[i];
    s[i][6] = v[i];
  }
  for (i = 0; i < n; ++i) {
    for (j = i; j < n; ++j)
      if (abs(s[j][i]) > u0) break;
    if (j >= n) break;
    if (i != j) swap(s[i], s[j]);
    for (j = 0; j < n; ++j)
      if (i != j) sub(s[j], s[i], s[j][i]/s[i][i]);
  }
  for (i = 0; i < n; ++i)
    b[i] = s[i][n]/s[i][i];
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      t[i][j] = 0;  
  for (i = 0; i < H/2; ++i)
    for (j = 0; j < W/2; ++j) {
      unsigned x = i, y = j;
      mod(x, y);
      t[x][y] = 255;
    }
  SaveImage(H*W, t);
}
