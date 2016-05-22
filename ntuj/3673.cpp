#include<cstdio>
const int N = 2012;
char tmp[N];
int t, p[N], c[N][N];
int go(int v) {
  if (p[v]) return 0;
  if (v == t) return 1;
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
    if (!go(0)) break;
    ++f;
  }
  return f;
}
main() {
  int T;
  scanf("%d", &T);
  int i, j, n;
  while (T--) {
    scanf("%d", &n);
    t = n*2 + 1;
    for (i = 0; i <= t; ++i)
      for (j = 0; j <= t; ++j)
        c[i][j] = 0;
    for (i = 0; i < n; ++i) {
      c[0][i+1] = c[n+i+1][t] = 1;
      scanf("%s", tmp);
      for (j = 0; j < n; ++j)
        c[i+1][n+j+1] = (tmp[j] == 'W');
    }
    if (flow() == n) puts("YES");
    else puts("NO");
  }
}
