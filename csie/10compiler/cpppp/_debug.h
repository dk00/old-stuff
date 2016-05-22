#ifndef _debug_h
#define _debug_h
#include<cstdio>
#include<cstring>
inline void p_node(const void *data) {
#ifdef DEBUG
  char buf[9];
  memcpy(buf, data, 4);
  buf[4] = 0;
  unsigned size, len;
  memcpy(&size, data + 8, 4);
  memcpy(&len, data + 4, 4);
  printf("+ %s [%u/%u]\n", buf, len, size);
#endif
}
#endif
