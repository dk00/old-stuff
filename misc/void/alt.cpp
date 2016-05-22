#include<set>
#include<cstdio>
#include<cstdlib>
#include<stdint.h>
typedef uint_fast8_t u8;
typedef uint_fast16_t u16;
typedef uint_fast64_t u64;
const int H = 6, W = H, Max = 5;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
struct pt { u8 x, y, d, o; };
struct State {
  u8 *c;
  pt *q;
  u8 n;
  u16 st, ed;
};
inline bool inboard(u8 x, u8 y) { return (x >= 0 && x < H && y >= 0 && y < W); }
inline u8& Lv(State &s, u8 x, u8 y) {
  return s.c[x*W+y];
}

inline u8 exp(State& s, u8 x, u8 y) {
  s.n -= Lv(s, x, y);
  Lv(s, x, y) = 0;
  for (u8 i = 0; i < 4; ++i) {
    s.q[s.ed] = (pt) {x + dx[i], y + dy[i], i, 0};
    if (inboard(s.q[s.ed].x, s.q[s.ed].y))
      ++s.ed;
  }
  return Lv(s, x, y) - Max;
}
inline pt next(pt a) {
  a.x += dx[a.d];
  a.y += dy[a.d];
  return a;
}
u8 sx[H*W*Max], sy[H*W*Max], qx[H*W*Max], qy[H*W*Max];
inline void rec(u8 x, u8 y, u8 i, u8 j) {
  for (;i < j; ++i)
    sx[i] = x, sy[i] = y;
}
void rec1(int n) {
  for (int i = 0; i < n; ++i)
    qx[i] = sx[i] , qy[i] = sy[i];
}

inline void step(State& s, u8 X = 0) {
  int x = s.q[s.st].x, y = s.q[s.st].y;
  s.q[s.st].o = Lv(s, x, y);
  s.q[s.ed] = next(s.q[s.st++]);
  if (Lv(s, x, y) > 0)
    ++s.n, ++Lv(s, x, y);
  else if (inboard(s.q[s.ed].x, s.q[s.ed].y))
    ++s.ed;
  if (X && Lv(s, x, y) >= Max)
    exp(s, x, y);
}
inline void undo(State& s, int st, int ed) {
  while (s.st > st) {
    --s.st;
    u8 x = s.q[s.st].x, y = s.q[s.st].y;
    s.n -= Lv(s, x, y);
    s.n += Lv(s, x, y) = s.q[s.st].o;
  }
  s.ed = ed;
}

void print(State s) {
  int i, j, k, n = 0;
  for (i = 0; i < H*W; ++i)
    if (s.c[i]) ++n;
  printf("-- %d %d %d\n", s.n, Max*n-s.n, s.n*10/n);
  for (i = 0; i < H; ++i, puts(""))
    for (j = 0; j < W; ++j) {
      k = s.c[i*W+j];
      if (k == 0) printf("  ");
      else if (k == Max) printf ("* ");
      else printf("%d ", k);
    }
}
int Link(State& s, u8 x, u8 y) {
  u16 i, j, nx, ny, r = 0, st = s.st, ed = s.ed;
  //while (s.st < s.ed) step(s);
  for (i = 0; i < 4; ++i) {
    j = 0, nx = x+dx[i], ny = y+dy[i];
    while (inboard(nx, ny)) {
      if ((j = Lv(s, nx, ny)) > 0) {++r; break;}
      nx += dx[i];
      ny += dy[i];
    }
  }
  //undo(s, st, ed);
  return r;
}

int Lim, hit = 0;
unsigned long long count = 0;
int go(u8 ap, u8 cost, State s) {
  ++count;
  u8 l, x, y, d, r = 0, order = 0, cost1;
  u16 &i = s.st, &j = s.ed, st = s.st, ed = s.ed, ed1;
  while (i < j) {
    if (cost > Lim) break;
    x = s.q[i].x, y = s.q[i].y;
    step(s);
    if (Lv(s, x, y) == 0) continue;
    d = Max - Lv(s, x, y);
    cost1 = cost + d;
    l = Link(s, x, y);
    if (cost1 <= Lim && order) r |= go(ap, cost, s);
    if (d > 0 && cost1 > Lim) continue;
    rec(x, y, cost, cost1);
    ed1 = s.ed;
    int tmp0 = Lv(s, x, y);
    exp(s, x, y);
    if (s.n == 0) {
      r = 2;
      rec1(cost1);
      Lim = cost1 - 1;
    }
    if (!d || cost1 > Lim || order) continue;
    if (go(ap, cost1, s)) r = 2;
    s.ed = ed1;
    Lv(s, x, y) = tmp0;
    s.n += tmp0;
  }
  undo(s, st, ed);
  return r;
}

int solve(State s) {
  const int O[] = {
    14, 15, 21, 20, 19, 13,
     8,  9, 16, 22, 27, 26,
    25,  7, 10, 28, 18, 12,
     2,  3, 17, 23, 33, 32,
    24,  6,  1,  4, 11, 29, 
    34, 31, 30,  0,  5, 35};
  int i, j, k, l;
  print(s);
  Lim = 77;
  for (count = j = 0; j < H*W; ++j) {
    i = O[j];
    k = Lv(s, i/W, i%W);
    if (k == 0) continue;
    //printf("%d %d\n", i/W, i%W);
    exp(s, i/W, i%W);
    rec(i/W, i%W, 0, Max-k);
    go(0, Max-k, s);
    Lv(s, i/W, i%W) = k;
    s.n += k;
    s.ed = 0;
  }
  printf("%d\t%d / %llu\n", Lim+1, hit, count);
  for (j = Lim; j > 0; --j)
    printf("(%d,%d)   ", qx[j], qy[j]);
  printf("(%d,%d)*\n", qx[j], qy[j]);
  return 0;
}

int readboard(State& s) {
  s.n = 0;
  for (int i = 0; i < H*W; ++i) {
    if (scanf("%d", s.c+i) != 1) return -1;
    s.n += s.c[i];
  }
  return 0;
}

u8 _c[H*W];
pt _q[H*W*H*Max];
void init(State &s) {
  s.c = _c;
  s.q = _q;
  s.n = s.st = s.ed = 0;
}

main() {
  State s;
  u16 n;
  init(s);
  while (readboard(s) != -1)
    solve(s);
}

