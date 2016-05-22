#include<cstdio>
const int N = 1601;
int p[N], d[N], num[N];
inline int find(int v) {
  if (v == p[v]) return v;
  return p[v] = find(p[v]);
}
inline void uni(int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b) return;
  if (d[a] < d[b]) p[a] = b;
  else p[b] = a;
  num[a] += num[b];
  num[b] = num[a];
  if (d[a] == d[b]) ++d[a];
}
main() {
  int T, C = 1;
  scanf("%d", &T);
  while (T--) {
    int i, j, n, m, sum = 0;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i) {
      scanf("%d", num+i);
      p[i] = i;
      d[i] = 0;
    }
    while (m--) {
      scanf("%d", &n);
      scanf("%d", &i);
      i = find(i - 1) + 1;
      while (--n > 0) {
        scanf("%d", &j);
        if (j > n) continue;
        uni(i - 1, j - 1);
        i = j;
      }
      scanf("%d", &j);
      if (num[i-1] < j) j = num[i-1];
      sum += j;
      num[i-1] -= j;
    }
    printf("Game #%d: %d\n", C++, sum);
  }
}
