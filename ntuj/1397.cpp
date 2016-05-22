#include<cstdio>
const int N = 55555;
long long s[N], x[N], y[N];
inline long long Sum(int a, int b) {
  if (a > b) return Sum(b, a);
  long long r = s[b-1] - (a? s[a-1]: 0) + x[b]*1ll*y[a] - y[b]*1ll*x[a];
  if (r < 0) return -r;
  return r;
}
main() {
  int i, j, n, m, C = 0;
  long long k, sum = 0;
  while (scanf("%d %d", &n, &m) == 2 && n+m) {
    if (C++) puts("");
    for (i = 0; i < n; ++i) {
      scanf("%lld %lld", x+i, y+i);
      s[i] = 0;
    }
    x[n] = x[0], y[n] = y[0];
    for (i = 0; i < n; ++i)
      s[i] = x[i]*1ll*y[i+1] - y[i]*1ll*x[i+1] + (i? s[i-1]: 0);
    sum = Sum(0, n);
    while (m--) {
      scanf("%d %d", &i, &j);
      k = Sum(i, j);
      if (k > sum - k)
        k = sum - k;
      printf("%lld.%lld\n", k/2, k%2*5);
    }
  }
}

