#include<cstdio>
#include<string>
#include<cstdint>
using namespace std;
int utf8_to_utf16(uint8_t to[], const string& from) {
  int i, j, n, m = from.length();
  uint8_t k;
  for (i = n = 0;i < m;i += j + 1) {
    for(k = from[i], j = 0;(k&0xC0) == 0xC0;++j, k<<=1);
    if(j < 1) {
      to[n++] = from[i];
      to[n++] = 0;
      continue;
    }
    to[n++] = (from[i+j]&0x3F)|(from[i+j-1]<<6);
    if (j < 2) {
      to[n++] = (from[i]>>2)&0x07;
      continue;
    }
    to[n++] = ((from[i+j-1]>>2)&0x0F)|(from[i+j-2]<<4);
    if (j < 3) continue;
    to[n] = to[n-2];
    to[n+1] = (to[n-1]&0x03)|0xDC;
    *(uint16_t *)(to+n-2) = ((to[n-1]>>2)&0x3F)|
      (((from[i+1]<<2)&0xC0) + ((from[i]&0x07)<<8) - 0x40)|0xD800;
    n += 2;
  }
  return n;
}

