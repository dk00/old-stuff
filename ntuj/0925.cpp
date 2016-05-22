#include<cstdio>
const int N = 100001;
unsigned m, un, c[2][N*32], u[2][N*32];
int max(unsigned x, int v = 0, int d = 30) {
  if (d < 0) return x;
  int to = !(x&(1<<d));
  if (u[to][v] == un)
    return max(x, c[to][v], d - 1) | (1<<d);
  return max(x, c[!to][v], d - 1) &~(1<<d);
}
int go(unsigned x) {
  int v = 0, d = 31, to;
  while (d--) {
    to = !!(x&(1<<d));
    if (u[to][v] != un) {
      u[to][v] = un;
      c[to][v] = m++;
    }
    v = c[to][v];
  }
}
unsigned s[N];
main() {
  int i, j, k, n, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%u", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d", s+i);
      if (i) s[i] ^= s[i-1];
    }
    k = s[0];
    m = 1;
    ++un;
    go(0);
    for (i = 0; i < n; ++i) {
      j = max(s[i]);
      if (j > k) k = j;
      go(s[i]);
    }
    printf("%d\n", k);
  }
}
