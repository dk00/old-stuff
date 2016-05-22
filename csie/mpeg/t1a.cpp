#include<cstdio>
#include"data.h"
#include"data.h"
struct vlc_table {
  int len[1337], pos[1337];
} table[9];

const int _B1[] = {1, 0, 2, 2, 2, 0, 2, 6, 0, 6, 12},
          _B2[] = {1, 1, 1, 0, 3, 1}, 
         _B2c[] = {0, 2, 2, 2, 2, 3},
          _B3[] = {0, 0, 1, 4, 12, 4, 8, 27, 6},
          _B4[] = {1, 0, 2, 2, 2, 0, 2, 6, 0, 6, 12, 0},
          _B5[] = {0, 2, 3, 1, 1, 1, 1}, 
         _B5b[] = {0, 3, 1, 1, 1, 1, 1, 1},
         _B5c[] = {0, 2, 1, 2, 3, 5, 4, 8, 0, 8, 0, 16, 16, 16, 16, 16};

void printbin(int c, int n) {
  int i, count = 0;
  for (i = 1<<(n-1); i > 0; i >>= 1) {
    printf("%d", !!(i&c));
    if (++count%4 == 0) printf(" ");
  }
  puts("");
}

void build_table(int id, const int num[], int L, bool rev = true) {
  int i, j, k, n, x, c, st, prev, pad;
  int *len = table[id].len, *pos = table[id].pos;
  prev = -1;
  for (i = j = x = st = 0; i < L; ++i, j <<= 1) {
    n = num[i];
    while (n--) {
      c = j;
      if (rev) c ^= (2<<i)-1;
      if (i >= 8) {
        c = j>>(i-7);
        if (rev) c ^= (1<<8)-1;
        if (c != prev) {
          printbin(c, 8);
          pos[c] = ++st;
          len[c] = 0;
          prev = c;
        }
        c = j&((1<<(i-7))-1);
        if (rev) c ^= ((1<<(i-7))-1);
      }
      pad = 7 - i;
      if (pad < 0) pad += 8;
      for (k = (1<<pad) - 1; k >= 0; --k) {
        len[st*256+((c<<pad)|k)] = (i&7)+1;
        pos[st*256+((c<<pad)|k)] = x;
      }
      printbin(c, i+1);
      ++x, ++j;
    }
  }
}

main() {

  build_table(0, _B5c, sizeof(_B5c)/sizeof(_B5c[0]));
  int i;
  /*for (i = 0; i < 1280; ++i)
    printf("%d %d\n", table[0].len[i], table[0].pos[i]);*/
}
