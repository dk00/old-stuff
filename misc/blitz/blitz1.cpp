#include<ctime>
#include<cstdio>
#include<algorithm>
#include"blitz.h"
#include"color.h"
using namespace std;

unsigned wait = 500, act_t = 250, W_Cross = 16, W_Hyper = 32;
unsigned c[BoardH][BoardW], nc[BoardH][BoardW], lc[BoardH][BoardW], 
         next[BoardH][BoardW], Count[NumColor];
int change[BoardH][BoardW];
unsigned unc[4096];
void Conv(unsigned c[BoardH][BoardW]) {
  int i, j, k;
  for (i = 0; i < BoardH; ++i)
    for (j = 0; j < BoardW; ++j) {      
      k = GetColor(c[i][j]);
      if (k != lc[i][j]) {
        if (change[i][j] < 0) change[i][j] = 0;
        ++change[i][j];
      }
      else {
        if (change[i][j] > 0) change[i][j] = 0;
        --change[i][j];
      }
      lc[i][j] = k;
      if (change[i][j] < -1) c[i][j] = k;
      else if (change[i][j] > 3 && !k) c[i][j] = 16;
      else c[i][j] = 0;
    }
}

inline void toXY(unsigned p, unsigned& x, unsigned& y, unsigned& nx, unsigned& ny) {
  x = p/2/BoardW;
  y = p/2%BoardW;
  nx = x + dx[2+p%2], ny = y + dy[2+p%2];
}

inline void toXY(unsigned p, unsigned& x, unsigned& y, unsigned& d) {
  x = p/2/BoardW;
  y = p/2%BoardW;
  d = 2 + p%2;
}

inline bool valid(unsigned x, unsigned y) {
  return (x >= 0 && x < BoardH && y >= 0 && y < BoardW);
}


const int N = BoardH*BoardW*2;
unsigned u[N];
int dg[N], act[N], conf[N][N], Lock[BoardH][BoardW];

inline int Effect(int p, int v = 0) {
  unsigned x, y, nx, ny;
  toXY(p, x, y, nx, ny);  
  if (!valid(x, y) || !valid(nx, ny) || Lock[x][y] || Lock[nx][ny]) return 0;  
  unsigned c0 = c[x][y]&7, c1 = c[nx][ny]&7, 
           v0 = c[x][y]&16, v1 = c[nx][ny]&16,
           q0 = c[x][y]&32, q1 = c[nx][ny]&32;
  if (c0 && c0 == c1) return 0;
  if (q0 || q1) {
    if (q0 && q1) return BoardH*BoardW;
    return 0;
    return Count[c0+c1] + v0 + v1 + 1;
  }
  int i, j, k, l, sc, add = 0, ex, ey;
  for (k = sc = 0; k < 2; ++k) {
    if (!c1) continue;
    if (sc > 0) ++add;
    for (i = 0; i < 2; ++i) {
      for (l = 0, j = 1; valid(ex = x+dx[i]*j, ey = y+dy[i]*j); ++j) {
        if ((nx == ex && ny == ey) || c1 != (c[ex][ey]&7)) break;
        Lock[ex][ey] += v;
        ++l;
      }
      for (j = 1; valid(ex = x-dx[i]*j, ey = y-dy[i]*j); ++j) {
        if ((nx == ex && ny == ey) || c1 != (c[ex][ey]&7)) break;
        Lock[ex][ey] += v;
        ++l;        
      }
      if (l == 2) sc += 1 + add;
      else if (l == 3) sc += 6 + add;
      else if (l >= 4) sc += l*8 - 22 + add;
    }
    swap(c0, c1);
    swap(x, nx);
    swap(y, ny);
  }
//  printf("%d %d %d %d %d\n", x, y, nx, ny, sc);
  return sc;
}

void Init() {
  int i, j;
  for (i = 0; i < NumColor; ++i)
    Count[i] = 0;
  for (i = 0; i < BoardH; ++i)
    for (j = 0; j < BoardW; ++j) {
      if (!nc[i][j] || clock() < next[i][j]) {
        c[i][j] = 0;
        continue;
      }
      c[i][j] = nc[i][j]&7;
      ++Count[c[i][j]];
      if (nc[i][j]&8) c[i][j] |= W_Cross;
      if (nc[i][j]&16) c[i][j] |= W_Hyper;
    }
  for (i = 0; i < N; ++i) {
    u[i] = Effect(i);
    dg[i] = 0;
    act[i] = 0;
  }
  for (i = 0; i < N; ++i) {
    if (u[i] < 1) continue;
    for (j = i+1; j < N; ++j)
      dg[i] += conf[i][j];
  }
}

/*
 * ooo = 250
 * oooo = 500 + 250 + 1050
 * ooooo = 2500 + 2750
 * ooxoo = 250 + 500 + 250 + 3750
 * */

int best, n_act, tmp[N], Act[N], count0;
int go(int sc,int d = 0) {
  int i, j, k, nsc;
  for (i = 0; i < N; ++i)
    if (act[i] == 0 && (nsc = Effect(i)) > 0) break;
  if (i >= N) {
    ++count0;
    if (sc > best) {
      best = sc;
      n_act = d;
      for (i = 0; i < d; ++i)
        Act[i] = tmp[i];
    }
    return 1;
  }
  act[i] = N;
  for (j = 0; j < N; ++j)
    if (conf[i][j]) --act[j];
  unsigned x, y, nx, ny;
  toXY(i, x, y, nx, ny);
  tmp[d] = i;
  Effect(i, 1);
  swap(c[x][y], c[nx][ny]);
  go(sc + nsc, d + 1);
  swap(c[x][y], c[nx][ny]);
  Effect(i, -1);
  for (j = 0; j < N; ++j)
    if (conf[i][j]) ++act[j];
  if (count0 > 15000) return 0;
  act[i] = -1;
  go(sc, d);
  act[i] = 0;
}

void test() {
  Dirc move[256];
  for (int i = 0; i < 256; ++i)
    move[i] = X;
  move['u'] = move['U'] = U;
  move['l'] = move['L'] = L;
  move['d'] = move['D'] = D;
  move['r'] = move['R'] = R;
  char cmd[99];  
  while (scanf("%s", cmd) == 1) {
    if (move[cmd[0]] != X) {
      int x, y;
      scanf("%d %d", &x, &y);
      SendMove(x, y, move[cmd[0]]);
      continue;
    }
    GetBoard(nc);
    int i, j, k;
    char name[]="bBGyRPYWO";
    for (i = 0; i < 8; ++i, puts(""))
      for (j = 0; j < 8; ++j) {
        printf("%02X ", nc[i][j]);
//        printf("%c ", name[c[i][j]]);
      }
    Init();
    puts("");
    for (i = 0; i < BoardH; ++i, puts(""))
      for (j = 0; j < BoardW; ++j)
        printf("%02X ", c[i][j]);
    count0 = best = n_act = 0;
    go(0);
    printf("= %d %d (%d)\n", best, n_act, count0);
    unsigned x, y, d;
    Select(0, -1);
    for (i = 0; i < n_act; ++i) {
      toXY(Act[i], x, y, d);
      printf("%2d: %u %u [%u]\n", Act[i], x, y, d);
      SendMove(x, y, (Dirc)d);
    }
  }
}

void test1() {
  int h0[8][8] = {
    {02,02,04,04,01, 06, 06, 07},
    {04,03,04,06,07, 06, 02, 07},
    {04,01,03,05,07, 07, 05, 06},
    {03,07,03,01,06, 04, 04, 02},
    {03,03,07,02,03, 01, 06, 05},
    {07,06,07,02,01, 07, 02, 03},
    {02,01,04,06,05, 05, 06, 04},
    {02,07,01,04,02, 02, 01, 05}};
  int i, j;
  for (i = 0; i < 8; ++i)
    for (j = 0; j < 8; ++j)
      c[i][j] = h0[i][j];
  printf ("%d %d %d %d\n", Effect(19), Effect(67), Effect(81), Effect(98));
  
}

main() {
  unsigned i, j, x0, y0, x1, y1, x2, y2, x3, y3;
  for (i = 0; i < N; ++i)
    for (j = 0;  j < N; ++j) {
      toXY(i, x0, y0, x1, y1);
      toXY(j, x2, y2, x3, y3);
      conf[i][j] = ((x0 == x2 && y0 == y2) || (x0 == x3 && y0 == y3) || 
        (x1 == x3 && y1 == y3) || (x1 == x2 && y1 == y2));
    }
  SetColor();
  while (!FindGameWindow()) sleep(250);
  puts("Found game window");
  test();
  while (1) {
    GetBoard(nc);
    Init();
    count0 = 0;
    n_act = best = 0;
    go(0);
    printf("= %d (%d)\n", best, count0);
    unsigned x, y, nx, ny, d;
    Select(0, -1);
    for (i = 0; i < n_act; ++i) {
      toXY(Act[i], x, y, d);
      toXY(Act[i], x, y, nx, ny);
      next[x][y] = clock() + wait;
      next[nx][ny] = clock() + wait;
      printf("%2d: %u %u [%u]\n", Act[i], x, y, d);
      SendMove(x, y, (Dirc)d);
    }
    sleep(150);
  }
}
