#include<cstdio>
main() {
  int i, n, m, T, C = 1;
  long long j, k;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %lld", &n, &k);
    for (i = j = 0; j < n*k; ++i)
      j += 1 + (j/n);
    printf("Case #%d: %d\n", C++, i);
  }
}
