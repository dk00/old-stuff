#include<cstdio>
const int M = 100001;
int s[M];
main() {
  int i, j, k, a, n, m;
  while (scanf("%d %d", &n, &m) == 2) {
    for (i = 0; i <= m; ++i) s[i] = i;
    while (n--) {
      scanf("%d %d", &j, &k);
      if ((k -= j) < 1) continue;
      for (i = j; i <= m; ++i) {
        a = s[i-j] + k;
        if (a > s[i]) s[i] = a;
      }
    }
    printf("%d\n", s[m]);
  }
}
