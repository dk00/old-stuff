#include<cstdio>
main() {
  int i, j, n, m, min, C = 1;
  while( scanf("%d %d", &n, &m) == 2 && n+m){
    for (i = 0; i < n; ++i) {
      scanf("%d", &j);
      if (i == 0) min = j;
      if (j < min) min = j;
    }
    for (i = 0; i < m; ++i)
      scanf("%d", &j);
    printf("Case %d: ", C++);
    if (m >= n) puts("0");
    else printf("%d %d\n", n - m, min);
  }
}
