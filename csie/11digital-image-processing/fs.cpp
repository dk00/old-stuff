#include"io.h"
using namespace std;
const int H = 256, W = 256, 
      dx[] = {1, 1, 1, 0}, dy[] = {1, 0, 0, 1}, w[] = {1, 3, 5, 7};
unsigned char s[H][W];
double t[H][W];
main() {
  LoadImage(H*W, s);
  int i, j, k;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
        t[i][j] = s[i][j];
  for (i = 0; i < H; ++i) {
    int r = 1;
    if (i%2) r = -1;
    for (j = 0; j < W; ++j) {      
      int y = (j*r + W)%W;
      double e = t[i][y];
      if (t[i][y] > 127.5) e = t[i][y] - 255;
      t[i][y] -= e;
      if (t[i][y] >= 127.5) s[i][y] = 255;
      else s[i][y] = 0;
      for (k = 0; k < 4; ++k) {
        int nx = i + dx[k], ny = y + dy[k]*r;
        if (nx >= H || ny >= W) continue;
        t[nx][ny] += e*w[k]/16;
      }
    }
  }

  SaveImage(H*W, s);
}
