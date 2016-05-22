#include<cstdio>
const int N = 500, inf = 100001;
int t, c[N][N];
void init(int ub) {
  for (i = 0; i <= t; ++i)
    for (j = 0; j <= t; ++j)
      c[i][j] = 0;
  for (i = 0; i <= n; ++i)
    for (j = 1; j <= n + 1; ++j)
      if (d[i][j] <= ub)
        c[i][n+j] = 1;
  for (i = 0; i < n; ++i)
    c[0][i+1] = c[n+i+1][j] = c[i+1][n+i+1] = 1;
}
int go(int v) {
  if (v == t) return 1;
  if (p[v]) return 0;
  p[v] = 1;
  for (int i = 0; i <= t; ++i)
    if (c[v][i]-- && go(i))
      return ++c[i][v];
    else ++c[v][i];
  return 0;
}
int flow() {
  int i, f = 0;
  while (1) {
    for (i = 0; i <= t; ++i) p[i] = 0;
    if (!go(0)) return f;
    ++f;
  }
}
main() {
  int i, j, k, a, m;
  while (scanf("%d %d", &n, &m) == 2) {
    t = n*2 + 1;
    for (i = 0; i < n+2; ++i) 
      for (j = 0; j < n+2; ++j)
        d[i][j] = inf;
    while (m--) {
      scanf("%d %d", &i, &j);
      scanf("%d", &d[i][j]);
    }
    scanf("%d", &m);
    a = -1;
    for (i = 0, j = inf; i <= j; ) {
      k = (i + j)/2;
      Init(k);
      if (flow(m) >= m) {
        a = k;
        j = k - 1;
      }
      else i = k + 1;
    }
    printf("%d\n", a);
  }
}
