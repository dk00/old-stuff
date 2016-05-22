#include<stdio.h>
#include<stdint.h>
uint32_t _h, _w, rl;

int writeHeader(FILE *fp, int32_t h, int32_t w) {
  const char head[] = "\x42\x4D\x39\x00\x00\x00\x00\x00\x00\x00\x36\x00\x00\x00\x28\x00\x00\x00\x01\x00\x00\x00\xFF\xFF\xFF\xFF\x01\x00\x18\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x20\x00\x00\x00\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
  _h = h, _w = w;
  fwrite(head, 1, sizeof(head), fp);
  rl = w*3;
  if (rl%4) rl += 4 - rl%4;
  uint32_t size = h*rl+54;
  fseek(fp, 2, SEEK_SET);
  fwrite(&size, sizeof(size), 1, fp);
  fseek(fp, 18, SEEK_SET);
  fwrite(&w, sizeof(w), 1, fp);
  fwrite(&h, sizeof(h), 1, fp);
  size -= 54;
  fseek(fp, 34, SEEK_SET);
  fwrite(&size, sizeof(size), 1, fp);
}

int writeBlock(int x, int y, int h, int w, uint8_t c[], FILE *fp) {
  x *= h*8, y *= w*8;
  int i, l, base;
  base = 54 + (_h-x-1)*rl + y*3;
  for (i = 0; i < h*8; ++i) {
    if (x+i >= _h) break;
    l = _w - y;
    if (w*8 < l) l = w*8;
    fseek(fp, base - i*rl, SEEK_SET);
    fwrite(c + i*w*8*3, sizeof(c[0]), l*3,fp);
  }
}
