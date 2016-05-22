#include<cstdio>
const int N = 92;
long long s[N];
main() {
  s[1] = 1;
  s[2] = 2;
  int i, j;
  long long n, m;
  for (i = 3; i < N; ++i)
    s[i] = s[i-1] + s[i-2];
  while (scanf("%lld", &n) == 1) {
    printf("%lld\n", n);
    m = n;
    for (j = 0, i = N - 1; i > 0; --i)
      if (n >= s[i]) {
        if (j++) putchar(' ');
        n -= s[i];
        printf("%d", i);
      }
    puts("");
    for (i = N - 1, j = 0; i > 0; --i)
      if (m >= s[i]) {
        if (j++) putchar(' ');
        m -= s[i];
        printf("%lld", s[i]);
      }
    puts("");
    puts("");
  }
}
