#include<cstdio>
const int N = 2222;
struct pt {
  int x, y;
  void operator-=(const pt& a) {
    x -= a.x;
    y -= a.y;
  }
  bool operator==(const pt& a) const {
    return (x*a.y == y*a.x && x*a.x >= 0 && y*a.y >= 0);
  }
  bool operator!=(const pt& a) const {
    return (x*a.y != y*a.x);
  }
} p[N], s[N];
bool fit(int a, int b) {
  double x = (p[a].x - p[b].x), y = (p[a].y - p[b].y);
  return (s[b].x*y - s[b].y*x)/(-s[a].x*1.0*s[b].y + s[a].y*1.0*s[b].x) >= 0;
}
int d[N];
main() {
  int i, n, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d %d", &s[i].x, &s[i].y);
      p[i] = s[i];
    }
    for (i = 1; i < n; ++i) {
      d[i] = n + 2;
      s[i-1] -= s[i];
    }
    --n;
    d[0] = 0;
    for (i = 1; i < n; ++i) {
      if (s[i] == s[i-1]) d[i] = d[i-1];
      else d[i] = d[i-1] + 1;
      if (i > 1 && s[i] != s[i-2] && fit(i - 2, i) && d[i-2] + 1 < d[i])
        d[i] = d[i-2] + 1;
    }
    printf("%d\n", d[n-1]);
  }
}
