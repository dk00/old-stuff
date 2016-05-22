#include<stdint.h>
#include"common.h"

const int N = 8, TSize = 1<<16;
uint8_t len[N][TSize], val[N][TSize];

void MakeTable(int id, uint8_t num[], uint8_t _v[]) {
  int i, j, k, x, q, c;
  uint8_t *l = len[id], *v = val[id];
  for (i = j = c = 0; i < 16; ++i) {
    c <<= 1;
    for (k = 0; k < num[i]; ++k, ++c) {
      for (x = 0; x < (1<<(15-i)); ++x) {
        v[(c<<(15-i))|x] = _v[j+k];
        l[(c<<(15-i))|x] = i+1;
      }
    }
    j += num[i];
  }
}

void next(FILE *fp, uint16_t& c, int& cl, uint8_t& tmp, int& tl, int u, int n) {
  cl -= u;
  c <<= u;
  while (cl < n) {
    if (tl < 1) {
      tl = 8;
      fread(&tmp, sizeof(tmp), 1, fp);
      //printf("[%02X] ", tmp);
      if (tmp == 0xFF) {
        fread(&tmp, sizeof(tmp), 1, fp);
        tmp = 0xFF;
      }
    }
    int m = n - cl;
    if (tl < m) m = tl;
    cl += m;
    c |= ((tmp>>(tl-m))&((1<<m)-1))<<(16-cl);
    tl -= m;
  }
}

inline int16_t neg(int16_t v, int j) {
  if (v&(1<<(j-1)))
    return v;
  return ((~0)<<j)|(v+1);
}

void DecBlock(int idd, int ida, int ci, FILE *fp, FLOAT r[], int rst) {

  static int cl = 0, tl = 0;
  static int16_t pred[3] = {0, 0, 0};
  static uint16_t c = 0;
  static uint8_t tmp;

  int i, j, k, x;
  uint8_t *l = len[idd], *v = val[idd];
  if (rst != 0)
    cl = tl = 0;
  next(fp, c, cl, tmp, tl, 0, 16);
  j = v[c], k = l[c];
  next(fp, c, cl, tmp, tl, k, j);
  pred[ci] += (j?neg(c>>(16-j), j): 0);
  r[0] = pred[ci];

  l = len[ida], v = val[ida];
  for (i = 1; i < 64; ++i) {
    next(fp, c, cl, tmp, tl, j, 16);
    j = v[c], k = l[c];
    next(fp, c, cl, tmp, tl, k, 0);
    if (j == 0) break;  // EOB
    for (x = 0; x < ((j>>4)&0xF); ++x)
      r[zz[i+x]] = 0;
    j &= 0xF;
    next(fp, c, cl, tmp, tl, 0, j);
    r[zz[i+=x]] = neg(c>>(16-j), j);
  }
  if (i >= 64) next(fp, c, cl, tmp, tl, j, 0);
  for (; i < 64; ++i) r[zz[i]] = 0;
}

