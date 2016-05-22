#include<cstdio>
const int N = 20002;
int s[N];
main() {
  int i, j, k, n, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0; i < n - 1; ++i)
      scanf("%d", s + i);
    for (i = 2, j = 0; i <= n; ++i)
      j = (j + s[n - i])%i;
    printf("%d\n", j + 1);
  }
}
