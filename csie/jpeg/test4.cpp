#include<stdio.h>
#include<stdint.h>
uint32_t start = 0, _h, _w;

int writeHeader(FILE *fp, int32_t h, int32_t w) {
  const char head[] = "\x42\x4D\x39\x00\x00\x00\x00\x00\x00\x00\x36\x00\x00\x00\x28\x00\x00\x00\x01\x00\x00\x00\xFF\xFF\xFF\xFF\x01\x00\x18\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x20\x00\x00\x00\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
  _h = w, _w = w;
  fwrite(head, 1, sizeof(head), fp);
  int32_t start = h*w*3+54;
  fseek(fp, 2, SEEK_SET);
  fwrite(&start, sizeof(start), 1, fp);
  fseek(fp, 18, SEEK_SET);
  fwrite(&w, sizeof(w), 1, fp);
  fwrite(&h, sizeof(h), 1, fp);
  int tmp = h*w*3;
  fseek(fp, 34, SEEK_SET);
  fwrite(&tmp, sizeof(tmp), 1, fp);
  fseek(fp, 54, SEEK_SET);
}

main() {
  int i, j, h = 16, w = 16;
  FILE *fp;
  fp = fopen("test.bmp", "wb");
  writeHeader(fp, h, w);
  unsigned char k = 128;
  for (i = 0; i < h; ++i)
    for (j = 0; j < w; ++j) {
      fwrite(&k, sizeof(k), 1, fp);
      fwrite(&k, sizeof(k), 1, fp);
      fwrite(&k, sizeof(k), 1, fp);
    }
  fclose(fp);
}
