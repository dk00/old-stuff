#ifndef _COMMON_H
#define _COMMON_H
#include<stdio.h>
#include<stdint.h>

typedef double FLOAT;

struct imginfo {
  int height, width;
  int nc, nc0, tq, mh, mw, cid[255], ch[255], cw[255], qt[255], sel[4], ht[4]; //XXX num
};

template<typename T> inline T byterev(T v) {
  T r = 0;
  for (int i = sizeof(T); i--; v >>= 8)
    r = (r<<8)|(v&0xFF);
  return r;
}

void DecBlock(int idd, int ida, int ci, FILE *fp, FLOAT r[], int rst = 0);
void readmarker(FILE *fp, imginfo& inf);
void readMB(imginfo& inf, FILE *fp, uint8_t r[]);

inline int Div(int a, int b) { return (a+b-1)/b; }

void MakeTable(int id, uint8_t num[], uint8_t _v[]);

void idct(FLOAT c[64]);

int writeHeader(FILE *fp, int32_t h, int32_t w);
int writeBlock(int x, int y, int h, int w, uint8_t c[], FILE *fp);

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
/*const int zz[] = {
  0,  1,  5,  6, 14, 15, 27, 28,
  2,  4,  7, 13, 16, 26, 29, 42,
  3,  8, 12, 17, 25, 30, 41, 43,
  9, 11, 18, 24, 31, 40, 44, 53,
 10, 19, 23, 32, 39, 45, 52, 54,
 20, 22, 33, 38, 46, 51, 55, 60,
 21, 34, 37, 47, 50, 56, 59, 61,
 35, 36, 48, 49, 57, 58, 62, 63
};*/

#endif
