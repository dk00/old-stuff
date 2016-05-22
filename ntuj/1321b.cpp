#include<cstdio>
const int N = 11111, M = 27;
int n, m, p[N], s[N][M], t[M][M], t1[M][M], u[N];
char a[N][M];
int best, ans[N];
int test() {
  int i, sum = 0;
  for (i = 0; i < n; ++i)
    if (a[i][ans[i]] - 'A' == ans[p[i]])
      ++sum;
  return sum;
}
void go(int d) {
  if (d >= n) {
    d = test();
    if (d > best) best = d;
    return;
  }
  for (int i = 0; i < m; ++i) {
    ans[d] = i;
    go(d+1);
  }
}
main() {
  int T, i, j, k, sum;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
      scanf("%d %s", p + i, a[i]), --p[i];
    best = 0;
    go(0);
    printf("%d\n", best);
  }
}
