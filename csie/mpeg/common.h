#ifndef _COMMON_H
#define _COMMON_H

#define Bitmask(n, m) (((1<<n)-1)<<m)

#include<stdint.h>
typedef double FLOAT;

struct vinfo {
  uint16_t width, height, mb_addr, mbn;
  uint8_t type, pattern, fwv, bwv, fwc, bwc, quant_scale;
  int16_t pred[3];
};

void gettable(int id, int *&len, int *&pos);

void vlc_init();

void idct(FLOAT c[64]);

inline int16_t neg(int16_t v, int j) {
  if (v&(1<<(j-1)))
    return v;
  return ((~0)<<j)|(v+1);
}

inline int32_t fix(int32_t v) {
  if ((v&1) == 0) {
    if (v < 0) ++v;
    if (v > 0) --v;
  }
  if (v > 2047)  return 2047;
  if (v < -2048) return -2048;
  return v;
}

const int zz[] = {
  0,  1,  8, 16,  9,  2,  3, 10,
 17, 24, 32, 25, 18, 11,  4,  5,
 12, 19, 26, 33, 40, 48, 41, 34,
 27, 20, 13,  6,  7, 14, 21, 28,
 35, 42, 49, 56, 57, 50, 43, 36,
 29, 22, 15, 23, 30, 37, 44, 51,
 58, 59, 52, 45, 38, 31, 39, 46,
 53, 60, 61, 54, 47, 55, 62, 63
};

const FLOAT _cm[3][3] = {
  {1.0, 1.0, 1.0},
  {0.0, -.34414, 1.772},
  {1.402, -.71414, 0.0}
};

int init_window(int w, int h, int interval);
void draw(uint8_t data[]);

#endif
