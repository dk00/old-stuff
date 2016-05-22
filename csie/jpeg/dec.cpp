#include<cstdio>
#include<string>
#include<stdint.h>
#include"common.h"
using namespace std;

void decode(imginfo& inf, FILE *fin, FILE *fout) {
  int i, x, y, h = Div(Div(inf.height, 8), inf.mh), w = Div(Div(inf.width, 8), inf.mw);
  uint8_t r[10*8*8*3];
  // XXX num. MB = h*w
  printf("%dx%d [%d:%d]\n", w, h, inf.mw, inf.mh);
  if (fout != NULL) writeHeader(fout, inf.height, inf.width);
  for (x = 0; x < h; ++x)
    for (y = 0; y < w; ++y) {
      readMB(inf, fin, r);
      if (fout != NULL) writeBlock(x, y, inf.mh, inf.mw, r, fout);
    }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    //XXX usage
    return 0;
  }
  FILE *fin = fopen(argv[1], "rb"), *fout = NULL;
  if (fin == NULL) return 0;
  imginfo inf;
  readmarker(fin, inf);
  if (argc > 2) {
    fout = fopen(argv[2], "wb");
    //XXX bmp header
  }
  decode(inf, fin, fout);
  if (fout != NULL) fclose(fout);
  fclose(fin);
}
