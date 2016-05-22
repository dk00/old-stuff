#include<set>
#include<cstdio>
#include<cstdlib>
#include<stdint.h>
/*
  v0 prototype  OK
  basic Solver
    XXX  IDA*
    TODO score
  v1 test     
 */
typedef uint_fast8_t u8;
typedef uint_fast16_t u16;
typedef uint_fast64_t u64;
const int H = 6, W = H, Max = 5;
const int Order[H*W] = {
21,22,23,24,25,26,
20, 7, 8, 9,10,27,
19, 6, 1, 2,11,28,
18, 5, 4, 3,12,29,
17,16,15,14,13,30,
36,35,34,33,32,31};
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
u8 sx[H*W*Max], sy[H*W*Max];
void rec(u8 x, u8 y, u8 i, u8 j) {
  for (;i < j; ++i)
    sx[i] = x, sy[i] = y;
}

inline void step(State& s) {
  int x = s.q[s.st].x, y = s.q[s.st].y;
  s.q[s.st].o = Lv(s, x, y);
  s.q[s.ed] = next(s.q[s.st++]);
  if (Lv(s, x, y) > 0)
    ++s.n, ++Lv(s, x, y);
  else if (inboard(s.q[s.ed].x, s.q[s.ed].y))
    ++s.ed;
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

u8 t, p[H*W*5+2], c[H*W*5+2][H*W*5+2];
u8 arg(u8 v) {
  if (v == t) return 1;
  if (p[v]) return 0;
  p[v] = 1;
  for (u8 i = 1; i <= t; ++i)
    if (c[v][i]-- && arg(i)) {
      ++c[i][v];
      return 1;
    } else ++c[v][i];
  return 0;
}
int flow() {
  int i, f = 0;
  while (1) {
    for (i = 0; i <= t; ++i) p[i] = 0;
    if (!arg(0)) break;
    ++f;
  }
  return f;
}

u8 test(State s) {
  u8 i, j, k, x, y, a, b, n, m, st = s.st, ed = s.ed;
  while (s.st < s.ed) step(s);
  m = H*W;
  n = m*4;
  t = n + m + 1;
  for (i = 0; i <= t; ++i)
    for (j = 0; j <= t; ++j)
      c[i][j] = 0;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j) {
      for (k = 0; k < 4; ++k) {
        x = i + dx[k], y = j + dy[k];
        if (!inboard(x, y)) continue;
        a = 1 + (x*W + y)*4 + k;
        b = 1 + (i*W + j)*4 + k;
        c[b][a] = H + W;
        b = 1 + n + x*W + y;
        if (Lv(s, i, j) > 0) c[0][a] = 1;
        c[a][b] = H + W;
      }
      if (Lv(s, i, j) == 0) continue;
      a = 1 + n + i*W + j;
      c[a][t] = Max - Lv(s, i, j);
    }
  undo(s, st, ed);
  flow();
  for (i = k = 0; i < H; ++i)
    for (j = 0; j < W; ++j) {
      a = 1 + n + i*W + j;
      k += c[a][t];
    }
  return k + 1;
}

u64 c0[H*W][Max];
u64 code(State& s) {
  u8 i, st = s.st, ed = s.ed;
  u64 c = 0;
  while (s.st < s.ed) step(s);
  for (i = 0; i < H*W; ++i)
    c ^= c0[i][s.c[i]];
  undo(s, st, ed);
  return c;
}
std::set<u64> R;
int hit = 0, count = 0;
int go(int lim, State s) {
  ++count;
  u8 x, y, d, r = 0;
  u16 &i = s.st, &j = s.ed, st = s.st, ed = s.ed;
  while (i < j) {
    x = s.q[i].x, y = s.q[i].y;
    step(s);
    if (Lv(s, x, y) == 0) continue;
    d = Max - Lv(s, x, y);
    if (d > 0 && go(lim, s)) r = 1;
    if (d > lim || r) break;
    if (d > 0) rec(x, y, lim-d, lim);
    lim -= d;
    exp(s, x, y);
    if (s.n == 0) r = 1;
    if (r) break;
    /*if (test(s) > lim) {
      ++hit;
      break;
    }*/
    u64 c0 = code(s);
    /*if (R.count(c0)) break;
    if (R.size() < 1000000) R.insert(c0);*/
  }
  undo(s, st, ed);
  return r;
}

void print(State s) {
  int i, j, k;
  printf("-- %d\n", s.n);
  for (i = 0; i < H; ++i, puts(""))
    for (j = 0; j < W; ++j) {
      k = s.c[i*W+j];
      if (k == 0) printf("  ");
      else if (k == Max) printf ("*");
      else printf("%d ", k);
    }
}

int solve(State s) {
  int i, j, k, l;
  print(s);
  printf("%d\n", test(s));
  for (l = 0; l <= 200; ++l) {
    R.clear();
    printf("%2d ", l);
    hit = count = 0;
    for (i = 0; i < H*W; ++i) {
      k = Lv(s, i/W, i%W);
      if (k < 1 || Max - k > l) continue;
      exp(s, i/W, i%W);
      rec(i/W, i%W, l-Max+k, l);
      j = go(l-Max+k, s);
      Lv(s, i/W, i%W) = k;
      s.n += k;
      s.ed = 0;
      if (j) {
        printf("%d / %d\n", hit, count);
        for (j = 0; j < l-1; ++j)
          printf("(%d,%d)   ", sx[j], sy[j]);
        printf("(%d,%d)*\n", i/W, i%W);
        return 1;
      }
    }
    printf(" %d / %d\n", hit, count);
  }
  puts("?");
  return 0;
}

void readboard(State& s) {
  s.n = 0;
  for (int i = 0; i < H*W; ++i) {
    scanf("%d", s.c+i);
    s.n += s.c[i];
  }
}

u8 _c[H*W];
pt _q[H*W*H*Max];
void init(State &s) {
  s.c = _c;
  s.q = _q;
  s.n = s.st = s.ed = 0;
  for (int i = 0; i < H*W; ++i)
    for (int j = 0; j < Max; ++j)
      c0[i][j] = ((rand()+1ll)<<40ll)^(rand()<<20ll)^rand();
}

main() {
  char cmd[99];
  State s;
  u16 n;
  init(s);
  while (scanf("%s", cmd) == 1) {
    if (cmd[0] == 'q') break;
    sscanf(cmd, "%d", &n);
    readboard(s);
    solve(s);
  }
}

