#include<cstdio>
const int inf = 2147483647;
main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d %d", &n, &m, &st, &ed);
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        c[i][j] = inf;
    while (m--) {
      scanf("%d %d", &i, &j);
      scanf("%d", &c[i][j]);
      c[j][i] = c[i][j];
    }
    for (i = 0, j = inf; i <=j;) {
      for (l = 0; l < n; ++l) u[l] = 0;
      u[st] = 1;
      u[ed] = 2;
      k = (i*1ll + j)/2;
      for (l = 0; l < n; ++l)
        if (c[st][l] < inf) {
          m = go(l, c[st][l]);
          if (
        }
    }
  }
}
