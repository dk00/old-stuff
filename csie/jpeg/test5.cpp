#include<cstdio>
main() {
  int i, j, base, x, y, st, h = 2, w = 2, mw = 2, sx = 0, sy = 0;
  base = (sx*h*8 * (mw*8) + sy*w*8)*3;
  printf("%d %d\n", sx, sy);
  for (i = 0; i < 64; ++i, puts("")) {
    printf("%d: ", i);
    for (x = 0; x < h; ++x) {
      for (y = 0; y < w; ++y) {
        j = base + ((x*8+i/8)*mw*8 + (y*8+i%8))*3;
        printf("%d ", j/3);
      }
    }
  }  
}
