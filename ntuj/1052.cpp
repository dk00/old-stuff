#include<cstdio>
main() {
  int i, n;
  long long sum;
  while (scanf("%d", &n) > 0 && n) {
    for (sum = 0, i = 1; i*1ll*i <= n; ++i)
      if (n%i == 0) {
        sum += i*8ll*!!(i%4);
        if (n/i != i) sum += n/i*8ll*!!(n/i%4);
      }
    printf("%lld\n", sum);
  }
}
