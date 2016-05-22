#include<cstdio>
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

void print(State s) {
  int i, j, k;
  printf("-- %d\n", s.n);
  for (i = 0; i < H; ++i, puts(""))
    for (j = 0; j < W; ++j) {
      k = s.c[i*W+j];
      if (k == 0) printf("  ");
      else if (k == Max) printf (" *");
      else printf(" %d", k);
    }
}

u8 sx[H*W*Max], sy[H*W*Max];
void rec(u8 x, u8 y, u8 i, u8 j) {
  for (;i < j; ++i)
    sx[i] = x, sy[i] = y;
}

int count = 0;
int go(int lim, State s) {
  ++count;
  u8 x, y, d, r = 0;
  u16 &i = s.st, &j = s.ed, st = s.st, ed = s.ed;
  while (i < j) {
    x = s.q[i].x, y = s.q[i].y;
    s.q[i].o = Lv(s, x, y);
    s.q[j] = next(s.q[i++]);
    if (Lv(s, x, y) == 0) {
      if (inboard(s.q[j].x, s.q[j].y)) ++j;
      continue;
    } 
    ++s.n;
    d = Max - ++Lv(s, x, y);
    if (d > 0 && go(lim, s)) r = 1;
    if (d > lim || r) break;
    if (d > 0) rec(x, y, lim-d, lim);
    lim -= d;
    exp(s, x, y);
    if (s.n == 0) r = 1;
    if (r) break;
  }
  while (i > st) {
    --i;
    x = s.q[i].x, y = s.q[i].y;
    s.n -= Lv(s, x, y);
    s.n += Lv(s, x, y) = s.q[i].o;
  }
  s.ed = ed;
  return r;
}

int solve(State s) {
  int i, j, k, l;
  print(s);
  for (l = 1; l <= 20; ++l) {
    printf("%2d ", l);
    count = 0;
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
        printf("%d\n", count);
        for (j = 0; j < l-1; ++j)
          printf("(%d,%d)   ", sx[j], sy[j]);
        printf("(%d,%d)*\n", i/W, i%W);
        return 1;
      }
    }
    printf("%d\n", count);
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
}

int test(int n, int s[]) {
  int i, j, k;
  for (i = j = 0; i < n; ++i) {
    if (s[i] == 0) continue;
    k = Max - s[i];
    if (k > j) k = j;
    j -= k;
    s[i] += k;
    ++j;
  }
  return j;
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

u8 test(State& s) {
  u8 i, j, k, x, y, a, b, n, m, r;
  m = H*W;
  n = m*4;
  t = n + m + 1;
  for (i = 0; i <= t; ++i)
    for (j = 0; j <= t; ++j)
      c[i][j] = 0;
  for (r = i = 0; i < H; ++i)
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
      r += c[a][t];
    }
  flow();
  for (i = k = 0; i < H; ++i)
    for (j = 0; j < W; ++j) {
      a = 1 + n + i*W + j;
      k += c[a][t];
      if (Lv(s, i, j) > 0)
        Lv(s, i, j) = Max - c[a][t];
    }
  print(s);
  printf("%d %d\n", k, r);
  return k;
}

void cval(State& s) {
  int i, j, k, a = 5, t[H][W];
  for (i = 0; i < H; ++i) {
    for (k = j = 0; j < W; ++j) {
      t[i][j] = k;
      if (Lv(s, i, j)) ++k;
      if (k == 1) k = a;
    }
    for (k = 0, j = W-1; j >= 0; --j) {
      t[i][j] += k;
      if (Lv(s, i, j)) ++k;
      if (k == 1) k = a;
    }
  }
  for (j = 0; j < W; ++j) {
    for (k = i = 0; i < H; ++i) {
      t[i][j] += k;
      if (Lv(s, i, j)) ++k;
      if (k == 1) k = a;
    }
    for (k = 0, i = H-1; i >= 0; --i) {
      t[i][j] += k;
      if (Lv(s, i, j)) ++k;
      if (k == 1) k = a;
    }
  }
  for (i = 0; i < H; ++i, puts(""))
    for (j = 0; j < W; ++j) {
      if (Lv(s, i, j) > 0)
        printf("%2d ", t[i][j]);
      else
        printf("   ");
    }
  puts("");
}
int Link(State& s, u8 x, u8 y) {
  u8 i, j, nx, ny;
  for (i = 0; i < 4; ++i) {
    nx = x+dx[i], ny = y+dy[i];
    while (inboard(nx, ny)) {
      if ((j = Lv(s, nx, ny)) > 0) break;
      nx += dx[i];
      ny += dy[i];
    }
    if (j == Max-1) return 1;
  }
  return 0;
}
/*
  3 3 4 4 4 1 
  3 4 * * * 2
 */
main() {
  char cmd[99];
  State s;
  u16 n;
  init(s);
  while (scanf("%s", cmd) == 1) {
    if (cmd[0] == 'q') break;
    sscanf(cmd, "%d", &n);
    readboard(s);
    print(s);
    int i, j;
    for (i = 0; i < H; ++i, puts(""))
      for (j = 0; j < W; ++j)
        printf(" %d", Link(s, i, j));
  }
}

