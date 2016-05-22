#include<cstdio>
#include<string>
#include<cstring>
#include<stdint.h>
#include"common.h"
using namespace std;

enum Marker {
  SOI = 0xD8,
  EOI = 0xD9,
  DQT = 0xDB,
  DHT = 0xC4,
  SOF = 0xC0,
  SOS = 0xDA
};

bool markertype(int x) {
  if (0xd0 <= x && x <= 0xd7) return 1;
  if (x == SOI || x == EOI || x == 0x01) return 1;
  return 0;
}

uint16_t _q[4][64];

void readQT(FILE *fp, int len) {
  while (len > 0) {
    uint8_t p = 1, t;
    fread(&t, sizeof(t), 1, fp);
    if (t&0xF0) p = 2; //precision
    t &= 0xF;          //dest
    int i;
    uint16_t *q = _q[t];
    printf("Quant Table [%d, %d]\n", p, t);
    for (i = 0; i < 64; ++i) {
      q[i] = 0;
      fread(q+i, p, 1, fp);
      printf("%d ", q[i]);
    }
    puts("");
    len -= 1 + p*64;
  }
}

void readHT(FILE *fp, int len) {
  while (len > 0) {
    uint8_t t;
    fread(&t, sizeof(t), 1, fp);
    printf("DHT %d,%d ", (t>>4)&0xF, t&0xF);
    t = ((t>>4)&0xF)|((t&0xF)<<1);
    printf(" (%d)\n", t);
    uint8_t num[16], val[333];
    int i, m = 0;
    fread(num, sizeof(num[0]), 16, fp);
    for (i = 0; i < 16; ++i)
      m += num[i];
    printf("num:");
    for (i = 0; i < 16; ++i)
      printf(" %d", num[i]);
    puts("");

    fread(val, sizeof(val[0]), m, fp);
    printf("val:");
    for (i = 0; i < m; ++i)
      printf(" %d", val[i]);
    puts("");
    MakeTable(t, num, val);
    len -= 17 + m;
  }
}

void readFrameHeader(FILE *fp, imginfo& inf) {
  uint8_t p, n;
  uint16_t w, h;
  fread(&p, sizeof(p), 1, fp);    //precision
  fread(&h, sizeof(h), 1, fp);
  fread(&w, sizeof(w), 1, fp);
  fread(&n, sizeof(n), 1, fp);    //n. component
  printf("Start of Frame %dx%d [%d]\n", byterev(w), byterev(h), p);
  inf.height = byterev(h), inf.width = byterev(w), inf.nc0 = n;
  int i;
  inf.mh = inf.mw = 0;
  for (i = 0; i < n; ++i) {
    uint8_t id, s, q;
    fread(&id, sizeof(id), 1, fp);//component id
    fread(&s, sizeof(s), 1, fp);  //sampling factor
    fread(&q, sizeof(q), 1, fp);  //quant dest
    inf.cid[i] = id;
    inf.ch[i] = s&0xF;
    inf.cw[i] = (s>>4)&0xF;
    inf.qt[i] = q;
    if (inf.ch[i] > inf.mh) inf.mh = inf.ch[i];
    if (inf.cw[i] > inf.mw) inf.mw = inf.cw[i];
    printf("#%d %d,%d quant #%d\n", id, (s>>4)&0xF, s&0xF, q);
  }
}

void readScanHeader(FILE *fp, imginfo& inf) {
  uint8_t n, sel[11], t[11], ss, se, ah;
  fread(&n, sizeof(n), 1, fp);
  inf.nc = n;
  printf("Start of Scan [%d]\n", n);
  int i, j;
  for (i = 0; i < n; ++i) {
    fread(sel+i, sizeof(sel[0]), 1, fp);
    fread(t+i, sizeof(t[0]), 1, fp);
    for (j = 0; j < inf.nc0;++j)
      if (inf.cid[j] == sel[i])
        inf.sel[i] = j;
    inf.ht[i] = t[i];
  }
  for (i = 0; i < n; ++i)
    printf(" %d:%d", sel[i], t[i]);
  puts("");
  fread(&ss, sizeof(ss), 1, fp);
  fread(&se, sizeof(se), 1, fp);
  fread(&ah, sizeof(ah), 1, fp);
}

void readmarker(FILE *fp, imginfo& inf) {
  uint16_t c = 0, len = 0;
  int next;
  while (fread(&c, 1, 2, fp) == 2) {
    if ((c&0xff) != 0xff) {
      printf("%04X invalid\n", c);
      return;
    }
    c >>= 8;
    if (markertype(c)) {
      printf("%04X\n", c);
      continue;
    }
    fread(&len, 1, 2, fp);
    len = byterev(len);
    printf("%04X %d\n", c, len);
    next = ftell(fp) + len - 2;
    if (c == DQT) readQT(fp, len-2);
    else if (c == DHT) readHT(fp, len-2);
    else if (c == SOF) readFrameHeader(fp, inf);
    else if (c == SOS) {
      readScanHeader(fp, inf);
      break;
    }
    fseek(fp, next, SEEK_SET);
  }
}

uint16_t pred[11];

inline FLOAT fix(FLOAT c) {
  if (c < -128) c = -128;
  if (c > 127) c = 127;
  return c;
}

FLOAT _c[10*8*8*3];
const FLOAT cm[3][3] = {
  {1.0, 1.0, 1.0},
  {0.0, -.34414, 1.772},
  {1.402, -.71414, 0.0}
};

void setBlock(imginfo& inf, FLOAT s[], int k, int sx, int sy) {
  int i, j, base, x, y, st, h = inf.mh/inf.ch[k], w = inf.mw/inf.cw[k];
  base = (sx*h*8 * (inf.mw*8) + sy*w*8)*3;
  for (i = 0; i < 64; ++i) {
    s[i] = fix(s[i]);
    if (k == 0) s[i] += 128; //XXX
    for (x = 0; x < h; ++x) {
      for (y = 0; y < w; ++y) {
        j = base + ((i/8*h+x)*inf.mw*8 + ((i%8)*w+y))*3;
        _c[j+2] += s[i]*cm[k][0];
        _c[j+1] += s[i]*cm[k][1];
        _c[j] += s[i]*cm[k][2];
      }
    }
  }
}

void readMB(imginfo& inf, FILE *fp, uint8_t r[]) { 
  int c, i, j, k, x, y, ac, dc;
  FLOAT s[64];
  uint8_t buf[10*8*8*3];
  memset(_c, 0, sizeof(_c));
  for (k = 0; k < inf.nc; ++k) {
    c = inf.sel[k];
    uint16_t *q = _q[inf.qt[c]];
    ac = inf.ht[k];
    dc = ((ac&0xF)<<1);
    ac = (((ac>>4)&0xF)<<1)|1;
    for (i = 0; i < inf.ch[c]; ++i)
      for (j = 0; j < inf.cw[c]; ++j) {
        DecBlock(dc, ac, k, fp, s);
        for (x = 0; x < 64; ++x)
          s[zz[x]] *= q[x];
        idct(s);
        setBlock(inf, s, k, i, j);
      }
  }
  for (i = 0; i < inf.mh*inf.mw*64*3; ++i) {
    j = _c[i] + .5;
    if (j < 0) j = 0;
    if (j > 255) j = 255;
    r[i] = j;
  }
}

