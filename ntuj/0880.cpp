#include<cstdio>
int n, s0[99], s1[99];
int go(int v, int a, int b, int c) {
  if (v >= n) {
    if (c) return (a<b?a:b) + 1;
    return 0;
  }
  int x, y;
  x = go(v + 1, a + s0[v], b + s1[v], c + 1);
  y = go(v + 1, a, b, c);
  return x>y?x:y;
  
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, k, sum0, sum1, max;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d %d", s0+i, s1+i);
    printf("%d\n", go(0, 0, 0, 0));
  }
}
