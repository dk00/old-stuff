const int NumColor = 7;
int Color[4096];
inline void SetColor() {
  int i;
  for (i = 0; i < 4096; ++i)
    Color[i] = -1;
  int table0[] = {0x05B, 0x2A3, 0xC12, 0xB2B, 0XB73, 0xCB1, 0xBBB, 0x579, 0x965, 0xA82};
  int table1[] = {1, 2, 4, 5, 3, 6, 7, 1, 3, 6};
  for (i = 0; i < sizeof(table0)/sizeof(table0[0]); ++i)
    Color[table0[i]] = table1[i];
}
inline int GetColor(int k) {
  if (Color[k] >= 0)  return Color[k];
  int  r = (k>>8)&15, g = (k>>4)&15, b = k&15;
  if (r < 8 && g < 8 && b < 8)
    return 0;
  int res = ((r>7)<<2)|((g>7)<<1)|(b>7);
  if ((res == 6 && r - g > 1) || (res == 4 && r - g < 4)) { 
    res = 3; // FIXME: Orange & Yellow
  }
  return res|8;
}
inline void Split(unsigned c, unsigned& r, unsigned& g, unsigned& b) {
  r = c >> 16;
  g = (c >> 8)&0xFF;
  b = c&0xFF;
}
unsigned raw[BoardH*GridH][BoardW*GridW];
inline void GetBoard(unsigned c[BoardH][BoardW]) {
  GetRawBoard(raw);
  int i, j, k, l, x, y;
  for (i = 0; i < BoardH; ++i)
    for (j = 0; j < BoardW; ++j) {
      int Count[8];
      for (k = 0; k < 8; ++k) Count[k] = 0;
      for (x = 10; x < 30; ++x)
        for (y = 10; y < 30; ++y) {
          unsigned r, g, b;
          Split(raw[i*GridH+x][j*GridW+y], r, g, b);          
          k = ((r>>7)<<2)|((g>>7)<<1)|(b>>7);          
          if (r > g && g > b) { //FIXME: Orange
            int t0 = r/2, t1 = 40;
            if (t0-t1 < g && g < t0+t1)
              k = 3;
          }
          /*if (i == 3 && j == 5)
            printf("[%d %d %d] %d\n", r, g, b, k);*/
          ++Count[k];
        }
      for (k = l = 0; k < 8; ++k)
        if (Count[k] > Count[l]) l = k;
      if (l == 7 || l == 0) {
        int tmp = 0;
        for (k = 1; k < 7; ++k)
          tmp += !!Count[k];
        if (tmp > 2 && Count[0] > 75 && Count[7] > 75)
          l = 16;
      }
      if (l == 3 && Count[1]*2 > Count[3]) l = 1;
      if (l == 7 && Count[7] < 230) {
        for (k = l = 0; k < 7; ++k)
          if (Count[k] > Count[l]) l = k;
      }
      if (l == 7 && Count[7] < 250) {
        printf("!Test > %d\n", l);
        for (k = 0; k < 8; ++k)
          printf("%d ", Count[k]);
        puts("");        
      }
      c[i][j] = l;
    }
}
