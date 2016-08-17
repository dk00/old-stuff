#include<cstdio>
main() {
  int i, j, n, T, C = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d", &j);
      if (i == n/2)
        printf("Case %d: %d\n", C++, j);
    }
  }
}
