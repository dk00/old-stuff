#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1000000;
struct pt {
  int x, y, c;
  bool operator<(pt a) const {
    return c < a.c;
  }
} s[N];
int p[N], d[N];
int find(int v) {
  if (v == p[v]) return v;
  return p[v] = find(p[v]);
}
int uni(int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b) return 0;
  if (d[a] < d[b]) p[a] = b;
  else p[b] = a;
  if (d[a] == d[b]) ++d[a];
  return 1;
}
main() {
  int i, j, n, m;
  while (scanf("%d %d", &n, &m) == 2 && n+m) {
    for (i = 0; i < n; ++i)
      p[i] = i, d[i] = 0;
    for (i = 0; i < m; ++i)
      scanf("%d %d %d", &s[i].x, &s[i].y, &s[i].c);
    sort(s, s+m);
    for (i = 0, j = 1; j < n && i < m; ++i)
      if (uni(s[i].x, s[i].y)) ++j;
    if (n == 0) puts("0");
    else if (j == n) printf("%d\n", s[i-1].c);
    else puts("IMPOSSIBLE");
  }
}
