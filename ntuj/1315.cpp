#include<cstdio>
const int N = 999;
int t, p[N], c[N][N];
int go(int v) {
  if (v == t) return 1;
  if (p[v]) return 0;
  p[v] = 1;
  for (int i = 1; i <= t; ++i)
    if (c[v][i]-- && go(i))
      return ++c[i][v];
    else ++c[v][i];
  return 0;
}
int flow() {
  int i, f = 0;
  while (1) {
    for (i = 0; i <= t; ++i) p[i] = 0;
    if (!go(0)) break;
    ++f;
  }
  return f;
}
main() {
  int i, j, k, n, m, T;
  n = 45;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &m);
    t = n + m + 1;
    for (i = 0; i <= t; ++i)
      for (j = 0; j <= t; ++j)
        c[i][j] = 0;
    for (i = 1; i <= n; ++i)
      c[0][i] = 1;
    for (j = 0; j < m; ++j) {
      scanf("%d", &c[n+1+j][t]);
      scanf("%d", &k);
      while (k--) {
        scanf("%d", &i);
        c[i][n+1+j] = 1;
      }      
    }
    if (flow() < 45) {
      puts("Oops!");
      continue;
    }
    for (i = 0; i < n; ++i) {
      for (j = 0; j < m; ++j)
        if (c[n+1+j][1+i]) break;
      printf("%d", j + 1);
      if (i%9 == 8) puts("");
      else printf(" ");
    }
  }
}
