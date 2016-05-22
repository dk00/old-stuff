#include<cstdio>
const int N = 1000005;
int p[N], d[N];
int find(int v) {
  if (v == p[v]) return v;
  return p[v] = find(p[v]);
}
int uni(int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b) return 1;
  if (d[a] < d[b]) p[a] = b;
  else p[b] = a;
  if (d[a] == d[b]) ++d[a];
  return 0;
}
main() {
  int i, j, k, n, m, C = 0;
  while (scanf("%d %d", &n, &m) == 2) {
    for (i = k = 0; i < n; ++i) 
      p[i] = i, d[i] = 0;
    while (m--) {
      scanf("%d %d", &i, &j);
      k += uni(i-1, j-1);
    }
    if (C++) puts("");
    printf("%d\n", k);
  }
}
