#include<cstdio>
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    t = n + 1;
    for (i = 0; i <= t; ++i)
      for (j = 0; j <= t; ++j)
        cap[i][j] = 0;
    base = 0;
    while (m--) {
      scanf("%d %d %d %d %d", &i &j, &k, &l, &x);
      if (x) {
        ++cap[0][j];
        ++cap[i][t];
      }
    }
  }
}
