#include<queue>
#include<cstdio>
using namespace std;
const int N = 4011;
struct pt {
  int x, y;
} s[N];
int d[N], p[N];
char c[200][200], u[N];
inline bool eq(pt a, int x, int y) {return (a.x == x && a.y == y);}
inline int adj(pt a, pt b) {
  if (a.x == b.y && a.y == b.x) return N*3;
  if((a.x == b.x || c[a.x][b.x]) && (a.y == b.y || c[a.y][b.y]))
    return (a.x != b.x)*1 + (a.y != b.y)*1;
  return N*3;
}
int len(int v) {
  if (v < 0) return 0;
  return 1 + len(p[v]);
}
void go(int v) {
  if (p[v] >= 0) go(p[v]);
  printf("%d %d\n", s[v].x, s[v].y);
}
main() {
  int i, j, k, n, m, s0, t0, s1, t1, st, ed;
  while (scanf("%d %d %d %d %d %d", &n, &m, &s0, &s1, &t0, &t1) > 0) {
    for (i = 0; i <= n; ++i)
      for (j = 0; j <= n; ++j)
        c[i][j] = 0;
    for (i = 0; i < m; ++i) {
      scanf("%d %d", &s[i].x, &s[i].y);
      c[s[i].x][s[i].y] = c[s[i].y][s[i].x] = 1;
      d[i] = d[m+i] = N*3;
      p[i] = p[m+i] = -1;
      s[m+i].x = s[i].y;
      s[m+i].y = s[i].x;
      if (eq(s[i], s0, s1)) st = i;
      if (eq(s[i], t0, t1)) ed = i;
      if (eq(s[m+i], s0, s1)) st = m+i;
      if (eq(s[m+i], t0, t1)) ed = m+i;
      u[i] = u[m+i] = 1;
    }
    m *= 2;
    d[st] = 0;
    queue<int> Q;
    Q.push(st);
    while (!Q.empty()) {
      i = Q.front();
      u[i] = 1;
      Q.pop();
      for (j = 0; j < m; ++j) {
        k = adj(s[i], s[j]);
        if (d[i] + k < d[j]) {
          d[j] = d[i] + k;
          p[j] = i;
          if (u[j]) u[j] = 0, Q.push(j);
        }
      }
    }
    int n0 = 0;
    printf("%d %d\n", d[ed], len(ed));
    go(ed);
  }
}
