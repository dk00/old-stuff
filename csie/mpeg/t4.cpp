#include<cstdio>
main() {
  printf("%d\n", ~0);
  int i, x, y, st, mb[16*16*3];
      for (x = 0; x < 32; ++x) {
        y = x/8*16*3*2 + x%8*2*3;
        mb[y]   = 1;
        mb[y+1] = 1;
        mb[y+2] = 1;
        mb[y+3] = 2;
        mb[y+4] = 2;
        mb[y+5] = 2;
        mb[y+48] = 3;
        mb[y+49] = 3;
        mb[y+50] = 3;
        mb[y+51] = 4;
        mb[y+52] = 4;
        mb[y+53] = 4;
      }  

  for (x = 0; x < 16; ++x, puts(""))
    for (y = 0; y < 16; ++y)
      printf("%d ", mb[x*16*3+y*3]);
}
