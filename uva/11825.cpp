#include<cstdio>
main() {
  int i, j, n, m, C = 1, d[99];
  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; ++i)
      d[i] = 0;
    for (i = 0; i < n; ++i) {
      scanf("%d", &m);
      while (m--) {
        scanf("%d", &j);
        ++d[j];
      }
    }
    for (i = j = 0; i < n; ++i)
      if (d[i] > d[j]) j = i;
    printf("Case %d: %d\n", C++, d[j] + 1);
  }
}
