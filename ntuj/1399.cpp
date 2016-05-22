#include<cstdio>
main() {
  int i, j, k, n, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 2, k = 1; i*1ll*i <= n; ++i) {
      for (j = 0; n%i == 0; ++j) {
        n /= i;
      if (j > k) k = j;
    }
    printf("%d\n", k);
  }
}
