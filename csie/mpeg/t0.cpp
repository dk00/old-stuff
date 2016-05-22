#include<cstdio>
#include<cstring>
#include<stdint.h>
#include"data.h"
#include"common.h"

enum Start_Codes {
  seq_header  = 0xB3010000,
  seq_end     = 0xB7010000,
  group_start = 0xB8010000,
  pic_start   = 0x00010000,
  slice_start = 0x01010000,
  ext_start   = 0xB5010000,
  user_data   = 0xB2010000
};

struct bindata {
  FILE *fp;
  uint_fast8_t rem, tmp;
};

uint8_t buf[1280*800*3];

inline bool openbin(bindata& bp, const char *name) {
  if (!name) return false;
  puts(name);
  bp.fp = fopen(name, "rb");
  bp.rem = 0;
  return bp.fp != NULL;
}

template<typename T> inline void readbin(bindata& bp, T& num) {
  fread(&num, sizeof(num), 1, bp.fp);
  bp.rem = 0;
}

inline uint_fast32_t readbit(bindata& bp, uint_fast32_t n) {
  uint_fast8_t x;
  uint_fast32_t r = 0;

  while (n > 0) {
    if (bp.rem < 1) {
      fread(&bp.tmp, sizeof(bp.tmp), 1, bp.fp);
      bp.rem = 8;
    }
    x = bp.rem;
    if (x > n) x = n;
    r = (r<<x)|(bp.tmp>>(bp.rem-x))&Bitmask(x, 0);
    bp.rem -= x;
    n -= x;
  }
  return r;
}

inline uint_fast32_t readvlc(bindata& bp, int tid) {
  uint_fast8_t i, j, c, l, a;
  int *len, *pos;

  gettable(tid, len, pos);
  i = 0;
  while (1) {
    if (bp.rem < 1) {
      bp.rem = 8;
      fread(&bp.tmp, sizeof(bp.tmp), 1, bp.fp);
      //printf("[%02X]", bp.tmp);
    }
    j = i;
    c = bp.tmp<<(8-bp.rem);
    l = len[j*256+c];
    a = pos[j*256+c];
    if (i > 0)  i = 0;
    if (l == 0) l = 8, i = pos[c];
    if (l > bp.rem) {
      fread(&bp.tmp, sizeof(bp.tmp), 1, bp.fp);
      //printf("[%02X]", bp.tmp);
      c |= bp.tmp>>bp.rem;
      bp.rem += 8;
      l = len[j*256+c];
      a = pos[j*256+c];
      i = 0;
      if (l == 0) l = 8, i = pos[c];
    }
    bp.rem -= l;
    if (i <= 0) break;
  }
  return a;
}

uint8_t intra_quant[64], nintra_quant[64];

inline uint32_t nextstc(bindata& bp) {
  uint32_t stc;
  uint8_t tmp;
  readbin(bp, stc);
  while ((stc<<8) != 0x01000000 || stc == ext_start || stc == user_data) {
    readbin(bp, tmp);
    stc >>= 8;
    stc |= tmp<<24;
  }
  return stc;
}

void dec_block(bindata& bp, vinfo& X, int i, uint8_t type, FLOAT r[64]) {
  int16_t j = 0, k = i-3, level;
  uint8_t size, run;
  uint16_t dc, ac;
  memset(r, 0, 64);

  if (k < 0) k = 0;
  if (mb_intra[X.type][type]) {
    if (i < 4)
      size = readvlc(bp, B5);
    else
      size = readvlc(bp, B5b);
    X.pred[k] += neg(readbit(bp, size), size)*8;
    r[0] = X.pred[k];
    ++j;
  } 
  if (X.type == 4)return;
  while(1) {
    ac = readvlc(bp, B5c);
    if (ac == 112) {
      if (j > 0) break;
      run = 0;
      level = 1;
    }
    if ((j > 0 || ac != 0) && ac != 111) {
      run = _run[ac];
      level = _level[ac];      
      if (readbit(bp, 1)) level = -level;
    }
    else {
      run = readbit(bp, 6);
      level = readbit(bp, 8);
      if (!(level&0x7F))
        level = (level<<8)|readbit(bp, 8);
    }
    j += run;
    r[zz[j]] = fix(2*level*X.quant_scale*intra_quant[j]/16);
  }
  idct(r);
}

void mb2buf(int h, int w, int addr, FLOAT c[], uint8_t buf[]) {
  int i, j, s0, s1, sx, sy, mh = (h+15)/16, mw = (w+15)/16;
  sx = addr/mw*16, sy = addr%mw*16;
  for (i = 0; i < 16 && sx+i < h; ++i)
    for (j = 0; j < 16 && sy+j < w; ++j) {
      s0 = (sx+i)*w*3 + (sy+j)*3; 
      s1 = i*16*3+j*3;
      buf[s0]   = c[s1];
      buf[s0+1] = c[s1+1];
      buf[s0+2] = c[s1+2];
    }
}

bool dec_mb(bindata& bp, vinfo& X) {
  uint8_t tid, type, pattern, esc = 0, mhfwr, mhbwr, mvfwr, mvbwr;
  uint16_t addr_inc;
  FLOAT c[64], mb[16*16*3];
  int i, mhfw, mhbw, mvfw, mvbw;
  while ((addr_inc = readvlc(bp, B1)+1) > 33) {
    if (addr_inc == 34) ++esc;
    if (addr_inc == 36) return false;
  }
  addr_inc += esc*33;
  X.mb_addr += addr_inc;
  tid = B2;
  if (X.type == 3) tid = B2c;
  type = readvlc(bp, tid);
  if (mb_quant[X.type][type]) 
    X.quant_scale = readbit(bp, 5);
  if (mb_mfw[X.type][type]) {
    mhfw = readvlc(bp, B4);
    if (X.fwc != 1 && mhfw)
      mhfwr = readbit(bp, X.fwc-1);
    mvfw = readvlc(bp, B4);
    if (X.fwc != 1 && mvfw)
      mvfwr = readbit(bp, X.fwc-1);
  }
  if (mb_mbw[X.type][type]) {
    mhbw = readvlc(bp, B4);
    if (X.bwc != 1 && mhbw)
      mhbwr = readbit(bp, X.bwc-1);
    mvbw = readvlc(bp, B4);
    if (X.bwc != 1 && mvbw)
      mvbwr = readbit(bp, X.bwc-1);
  }
  int j = -1;
  X.pattern = 0;
  if (mb_intra[X.type][type]) X.pattern = 63;
  if (mb_pattern[X.type][type]) {
    X.pattern = cbp[j=readvlc(bp, B3)];
  }
  //printf("MB +%d type %d pattern %d:%d\n", addr_inc, type, j, cbp[j]);
  for (i = 0; i < 6; ++i) {
    if (!(X.pattern&(1<<i))) continue;
    dec_block(bp, X, i, type, c);
    uint_fast16_t st, x, y, base;
    if (i < 4) {
      st = 3*8*(i%2) + 3*16*8*(i/2);
      for (x = 0; x < 64; ++x) {
        y = st + x/8*16*3 + x%8*3;
        mb[y]   = c[x];
        mb[y+1] = c[x];
        mb[y+2] = c[x];
      }
    } else {
      const FLOAT *cm = _cm[i-3];
      for (x = 0; x < 64; ++x) {
        y = x/8*16*3*2 + x%8*2*3;
        mb[y]   += c[x]*cm[0];
        mb[y+1] += c[x]*cm[1];
        mb[y+2] += c[x]*cm[2];
        mb[y+3] += c[x]*cm[0];
        mb[y+4] += c[x]*cm[1];
        mb[y+5] += c[x]*cm[2];
        mb[y+48] += c[x]*cm[0];
        mb[y+49] += c[x]*cm[1];
        mb[y+50] += c[x]*cm[2];
        mb[y+51] += c[x]*cm[0];
        mb[y+52] += c[x]*cm[1];
        mb[y+53] += c[x]*cm[2];
      }
    }
  }
  mb2buf(X.height, X.width, X.mb_addr-1, mb, buf);
  if (X.type == 4)
    readbit(bp, 1);
  return true;
}

void dec_slice(bindata& bp, vinfo& X) {
  uint8_t quant_scale;
  quant_scale = readbit(bp, 5);
  //printf("slice / quant scale %d\n", quant_scale);
  while (readbit(bp,  1))
    readbit(bp,  8);
  X.pred[0] = X.pred[1] = X.pred[2] = 1024;
  int i;
  for (i = 0; ; ++i) {
    X.quant_scale = quant_scale;
    if (!dec_mb(bp, X)) break;
  }
  fseek(bp.fp, -1, SEEK_CUR);
}

void dec_pic(bindata& bp, vinfo& X) {
  uint16_t vbv_delay;
  uint32_t stc, ref;
    ref       = readbit(bp, 10);
    X.type    = readbit(bp,  3);
    vbv_delay = readbit(bp, 16);
  if (X.type == 2 || X.type == 3) {
    X.fwv     = readbit(bp,  1);
    X.fwc     = readbit(bp,  3);
  }
  if (X.type == 3) {
    X.bwv     = readbit(bp,  1);
    X.bwc     = readbit(bp,  3);
  }
  while (readbit(bp, 1))
    readbit(bp, 8);
  printf("Pic type %d / ref %d / vbv delay %d / fw %d:%d\n", X.type, ref, vbv_delay, X.fwv, X.fwc);
}

void dec_gop(bindata& bp) {
  uint32_t tc, stc;
  uint8_t closed, link;
  tc     = readbit(bp, 25);
  closed = readbit(bp,  1);
  link   = readbit(bp,  1);
}

void dec_seqhead(bindata& bp, vinfo& X) {
  int i;
  uint32_t bitrate;
  uint16_t vbv_size;
  uint8_t ar, fps;
  X.width  = readbit(bp, 12); 
  X.height = readbit(bp, 12);
  ar       = readbit(bp,  4);
  fps      = readbit(bp,  4);
  bitrate  = readbit(bp, 18);
/*marker*/   readbit(bp,  1);
  vbv_size = readbit(bp, 10);
  //init_window(X.width, X.height);

  printf("%u x %u\n", X.width, X.height);
  if (readbit(bp, 1)) 
    for (i = 0; i < 64; ++i)
      intra_quant[i] = readbit(bp, 8);
  else for (i = 0; i < 64; ++i)
    intra_quant[i] = intra_quant_def[i];
  if (readbit(bp, 1)) //must be byte aligned here
    fread(nintra_quant, 1, 64, bp.fp);
  else for (i = 0; i < 64; ++i)
    nintra_quant[i] = 16;
}

void dec_bitstream(bindata& bp) {
  int i, count = 0;
  uint32_t stc;
  vinfo X;
  
  puts("test");
  for (i = 0; i < 3; ++i) {
    stc = nextstc(bp);
    //printf("%d %08X\n", count, stc);
    //if (stc == pic_start || stc == seq_end) Draw(buf);

    if (stc == seq_end) break;
    if (stc == seq_header)  dec_seqhead(bp, X);
    if (stc == group_start) dec_gop(bp);
    if (stc == pic_start)   dec_pic(bp, X), ++count;
    if (stc == slice_start) dec_slice(bp, X);
  }
}

int main(int argc, char **argv) {
  vlc_init();
  bindata bp;
  if (!openbin(bp, argv[1])) {
    puts("Error: open file");
    return 0;
  }
  dec_bitstream(bp);
  fclose(bp.fp);
}
