#include<cstdio>
#include<algorithm>
using namespace std;
int p[99], d[99];
int find(int v) {
  if (p[v] == v) return v;
  return p[v] = find(p[v]);
}
bool uni(int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b) return false;
  if (d[a] < d[b]) p[a] = b;
  else p[b] = a;
  if (d[a] == d[b]) ++d[a];
  return true;
}
int n, m;
void init() {
  for (int i = 0; i < n; ++i)
    p[i] = i, d[i] = 0;
}
const int N = 10005, inf = 2147483647;
struct pt {
  int x, y, b, c;
  bool operator<(pt a) const {return c < a.c;}
} s[N], t[N];
int test(int lb) {
  int i, j, k, tn;
  init();
  for (i = tn = 0; i < m; ++i)
    if (s[i].b >= lb) t[tn++] = s[i];
  sort(t, t + tn);
  for (i = j = 0, k = 1; i < tn; ++i)
    if (uni(s[i].x, s[i].y)) ++k, j += t[i].c;
  if (k < n) return inf;
  return j;
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, a, c;
    scanf("%d %d %d", &n, &m, &c);
    j = 1000000, k = 0;
    for (i = 0; i < m; ++i) {
      scanf("%d %d %d %d", &s[i].x, &s[i].y, &s[i].b, &s[i].c);
      if (s[i].b < j) j = s[i].b;
      if (s[i].b > k) k = s[i].b;
    }
    a = 0;
    while (j <= k) {
      i = (j + k)/2;
      if (test(i) <= c) a = i, j = i + 1;
      else k = i - 1;
    }
    if (a > 0) printf("%d kbps\n", a);
    else puts("streaming not possible.");
  }
}
