#include<cstdio>
int st, len, s[2012], p[2012];
void gen(int a, int b, int c, int m) {
  int i;
  for (i = 0; i < m; ++i) p[i] = -1;
  for (i = 0; p[s[i]] < 0; ++i) {
    p[s[i]] = i;
    s[i+1] = (c + s[i]*(b + s[i]*a))%m;
  }
  st = p[s[i]];
  len = i - st;
}
main() {
  int a, b, c, m, k, s0;
  while (scanf("%d %d %d %d %d %d", s, &a, &b, &c, &m, &k) == 6) {
    s0 = s[0];
    s[0] %= m;
    gen(a, b, c, m);
    if (k > st)
      k = st + (k - st)%len;
    s[0] = s0;
    printf("%d\n", s[k]);
  }
}
