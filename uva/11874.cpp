#include<cstdio>
const int N = 101, inf = 2000000000;
int n, d[N], o[N], c[N][N];
void sp() {
  int i, j;
  for (i = 0; i < n; ++i) {
    if (d[i] <= o[i]) continue;
    o[i] = d[i];
    for (j = 0; j < n; ++j)
      if (c[i][j] > -inf && d[i] + c[i][j] > d[j])
        d[j] = d[i] + c[i][j];
  }
}
main() {
  int i, j, k, m, x, T, C = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d", &n, &m, &x);
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        c[i][j] = -inf;
    while (m--) {
      scanf("%d %d", &i, &j);
      scanf("%d", &c[i][j]);
      scanf("%d", &k);
      c[i][j] -= x*k;
    }
    for (i = 0; i < n; ++i)
      o[i] = -1, d[i] = 0;
    for (i = 0; i < n; ++i)
      sp();
    for (i = x = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        if (d[i] + c[i][j] > d[j])
          x = 1;
    printf("Case %d: %s\n", C++, x?"YES":"NO");
  }
}
