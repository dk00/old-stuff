#include"data.h"
#include"common.h"
#include<cstdio>

struct vlc_table {
  int len[1337], pos[1337];
} table[9];

const int _B1[] = {1, 0, 2, 2, 2, 0, 2, 6, 0, 6, 12},
          _B2[] = {1, 1, 1, 0, 3, 1}, 
         _B2c[] = {0, 2, 2, 2, 2, 3},
          _B3[] = {0, 0, 1, 4, 12, 4, 8, 27, 6},
          _B4[] = {1, 0, 2, 2, 2, 0, 2, 6, 0, 6, 12, 0},
          _B5[] = {0, 2, 3, 1, 1, 1, 1}, 
         _B5b[] = {0, 3, 1, 1, 1, 1, 1, 1};

const uint16_t _B5c[113][2] = {
  { 0x3, 2 }, { 0x4, 4 }, { 0x5, 5 }, { 0x6, 7 },
  { 0x26, 8 }, { 0x21, 8 }, { 0xa, 10 }, { 0x1d, 12 },
  { 0x18, 12 }, { 0x13, 12 }, { 0x10, 12 }, { 0x1a, 13 },
  { 0x19, 13 }, { 0x18, 13 }, { 0x17, 13 }, { 0x1f, 14 },
  { 0x1e, 14 }, { 0x1d, 14 }, { 0x1c, 14 }, { 0x1b, 14 },
  { 0x1a, 14 }, { 0x19, 14 }, { 0x18, 14 }, { 0x17, 14 },
  { 0x16, 14 }, { 0x15, 14 }, { 0x14, 14 }, { 0x13, 14 },
  { 0x12, 14 }, { 0x11, 14 }, { 0x10, 14 }, { 0x18, 15 },
  { 0x17, 15 }, { 0x16, 15 }, { 0x15, 15 }, { 0x14, 15 },
  { 0x13, 15 }, { 0x12, 15 }, { 0x11, 15 }, { 0x10, 15 },
  { 0x3, 3 }, { 0x6, 6 }, { 0x25, 8 }, { 0xc, 10 },
  { 0x1b, 12 }, { 0x16, 13 }, { 0x15, 13 }, { 0x1f, 15 },
  { 0x1e, 15 }, { 0x1d, 15 }, { 0x1c, 15 }, { 0x1b, 15 },
  { 0x1a, 15 }, { 0x19, 15 }, { 0x13, 16 }, { 0x12, 16 },
  { 0x11, 16 }, { 0x10, 16 }, { 0x5, 4 }, { 0x4, 7 },
  { 0xb, 10 }, { 0x14, 12 }, { 0x14, 13 }, { 0x7, 5 },
  { 0x24, 8 }, { 0x1c, 12 }, { 0x13, 13 }, { 0x6, 5 },
  { 0xf, 10 }, { 0x12, 12 }, { 0x7, 6 }, { 0x9, 10 },
  { 0x12, 13 }, { 0x5, 6 }, { 0x1e, 12 }, { 0x14, 16 },
  { 0x4, 6 }, { 0x15, 12 }, { 0x7, 7 }, { 0x11, 12 },
  { 0x5, 7 }, { 0x11, 13 }, { 0x27, 8 }, { 0x10, 13 },
  { 0x23, 8 }, { 0x1a, 16 }, { 0x22, 8 }, { 0x19, 16 },
  { 0x20, 8 }, { 0x18, 16 }, { 0xe, 10 }, { 0x17, 16 },
  { 0xd, 10 }, { 0x16, 16 }, { 0x8, 10 }, { 0x15, 16 },
  { 0x1f, 12 }, { 0x1a, 12 }, { 0x19, 12 }, { 0x17, 12 },
  { 0x16, 12 }, { 0x1f, 13 }, { 0x1e, 13 }, { 0x1d, 13 },
  { 0x1c, 13 }, { 0x1b, 13 }, { 0x1f, 16 }, { 0x1e, 16 },
  { 0x1d, 16 }, { 0x1c, 16 }, { 0x1b, 16 },
  { 0x1, 6 }, { 0x2, 2 }  
};

void gettable(int id, int *&len, int *&pos) {
  len = table[id].len;
  pos = table[id].pos;
}

void build_table(int id, const int num[], int L, bool rev = true) {
  int i, j, k, n, x, c, st, prev, pad;
  int *len = table[id].len, *pos = table[id].pos;
  for (i = 0; i < 4*256; ++i) len[i] = 8;
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
      ++x, ++j;
    }
  }
}

int m = 1;
void add_code(int id, int c, int l, int p) {
  int i, st = 0, *len = table[id].len, *pos = table[id].pos;
  if (l > 8) {
    i = c>>(l-8);
    if (pos[i] <= 0) pos[i] = m++;
    st = pos[i];
    c &= (1<<(l-8))-1;
    l -= 8;
  }
  for (i = (1<<(8-l))-1; i >= 0; --i) {
    len[st*256+((c<<(8-l))|i)] = l;
    pos[st*256+((c<<(8-l))|i)] = p;
  }
}

void vlc_init() {
  build_table(B1, _B1, sizeof(_B1)/sizeof(_B1[0]));
  build_table(B2, _B2, sizeof(_B2)/sizeof(_B2[0]));
  build_table(B2c, _B2c, sizeof(_B2c)/sizeof(_B2c[0]));
  build_table(B3, _B3, sizeof(_B3)/sizeof(_B3[0]));
  build_table(B4, _B4, sizeof(_B4)/sizeof(_B4[0]));
  build_table(B5, _B5, sizeof(_B5)/sizeof(_B5[0]), 0);
  build_table(B5b, _B5b, sizeof(_B5b)/sizeof(_B5b[0]), 0);
  int i, *len = table[B1].len, *pos = table[B1].pos;
  pos[0] = 35;
  pos[1] = 4;
  for (i = (1<<5)-1; i >= 0; --i) {
    len[4*256+i] = len[4*256+(i|0xE0)] = 3;
    pos[4*256+i] = 33;
    pos[4*256+(i|0xE0)] = 34;
  }
  pos = table[B5].pos;
  for (i = 0; i < 256; ++i) {
    if (pos[i] < 2) ++pos[i];
    else if (pos[i] == 2) pos[i] = 0;
  }
  for (i = 0, m = 1; i < 113; ++i)
    add_code(B5c, _B5c[i][0], _B5c[i][1], i);
}
