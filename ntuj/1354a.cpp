#include<cstdio>
const int N = 1001, M = 10056;
int s[N];
int m;
int go(int d, int n, int i) {
  if (n >= m) return 1;
  int sum = 0;
  if (i + 1 < m)
    sum += go(d, n, i + 1);
  if (i < m && s[i]) {
    s[i] = 0;
    sum += go(d, n + 1, i + 1);
    if (n + 1 < m)
      sum += go(d + 1, n + 1, 0);
    s[i] = 1;
  }
  return sum;
}
main() {
  int i, j, T;
  s[0] = 1;
  for (i = 1; i <= N; ++i) {
    s[i] = s[i-1];
    for (j = 1; j < i; ++j) {
      s[i] += (s[j-1] + s[j]) * s[i-j];
      if (s[i] < 0)
        printf("%d\n", s[i]);
      s[i] %= M;
    }
  }
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &m);
    for (i = 0; i < m; ++i)
      s[i] = 1;
    printf("%d\n", go(0, 0, 0));
  }
}
