#include<cstdio>
const int N = 15555, M = 100000007;
inline int Add(int a, int b) { return (a + b)%M; }
inline int Mul(long long a, int b) { return a*1ll*b%M; }
int s[N], t[N];
inline int Sum(int x, int y) {
  return Add(t[y], M - (x - 1 >= 0? t[x-1]: 0));
}
main() {
  int i, j, k, n, m;
  while (scanf("%d %d %d", &n, &k, &m) == 3) {
    for (i = 0; i <= m; ++i) s[i] = 0;
    s[0] = 1;
    while (n--) {
      for (j = 0, i = 1; i <= m && i < k; ++i)
        j = Add(j, Mul(s[m-i], i));
      t[0] = s[0];
      for (i = 1; i <= m; ++i)
        t[i] = Add(s[i], t[i-1]);
      for (i = m; i >= 0; --i) {
        if (i >= k) j = Add(j, Mul(s[i-k], k));
        s[i] = j;
        j = Add(j, M - Sum(i - k, i - 1));
      }
    }
    printf("%d\n", s[m]);
  }
}
