#include<queue>
#include<cstdio>
using namespace std;
const int N = 501 , inf = 1<<30, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
struct pt {
  int x, y, z;
}s[N], o[N];
int n, m, n0, n1, h[N][N], d[N][N], t, c0[N][N], c[N][N], p[N];
void go(pt p, int type) {
  int i, j;
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
        d[i][j] = inf;
  queue<pt> Q, N;
  d[--p.x][--p.y] = 0;
  Q.push(p);
  while (!Q.empty() || !N.empty()) {
    if (Q.empty()) {
      p = N.front();
      N.pop();
    }
    else {
      p = Q.front();
      Q.pop();
    }
    for (i = 0; i < 4; ++i) {
      pt a;
      a.x = p.x + dx[i];
      a.y = p.y + dy[i];
      if (a.x < 0 || a.x>=n || a.y < 0 || a.y >= m)
        continue;
      int nd = d[p.x][p.y];
      if (type*(1-nd%2*2)*(h[p.x][p.y] - h[a.x][a.y]) > 0)
        ++nd;
      if (nd >= d[a.x][a.y]) continue;
      d[a.x][a.y] = nd;
      if (nd == d[p.x][p.y]) Q.push(a);
      else N.push(a);
    }
  }
}
void Init(int x) {
  int i, j;
  t = n0*2 + n1 + 1;
  for (i = 0; i <= t; ++i)
    for (j = 0; j <= t; ++j)
      c[i][j] = 0;
  for (i = 0; i < n0*2; ++i)
    c[0][i+1] = 1;
  for (j = 0; j < n1; ++j)
    c[2*n0 + j + 1][t] = o[j].z;
  for (i = 0; i < n0*2; ++i)
    for (j = 0; j < n1; ++j)
      c[i+1][2*n0+j+1] = (x >= c0[i][j]);
}
int go(int v) {
  if (v == t) return 1;
  if (p[v])return 0;
  p[v] = 1;
  for (int i = 1; i <= t; ++i)
    if (c[v][i]-- && go(i)) return ++c[i][v];
    else ++c[v][i];
  return 0;
}
int flow() {
  int sum = 0;
  while (1) {
    for (int i = 0; i <= t; ++i) p[i] = 0;
    if (!go(0)) break;
    ++sum;
  }
  return sum;
}
main() {
  int i, j, k, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d %d", &n, &m, &n0, &n1);
    for (i = 0; i < 2*n0; ++i) 
      scanf("%d %d", &s[i].x, &s[i].y);
    scanf("%*d %*d");
    for (i = 0; i < n1; ++i)
      scanf("%d %d %d", &o[i].x, &o[i].y, &o[i].z);
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j)
        scanf("%d", &h[i][j]);
    for (i = 0; i < 2*n0; ++i) {
      go(s[i], 1 - i/n0*2);
      for (j = 0; j < n1; ++j)
        c0[i][j] = d[o[j].x-1][o[j].y-1];
    }
    for (i = 0, j = 2*n0; i <= j;) {
      k = (i + j)/2;
      Init(k);
      if (k + flow() >= 2*n0) m = k, j = k - 1;
      else i = k + 1;
    }
    printf("%d\n", m);
  }
}
