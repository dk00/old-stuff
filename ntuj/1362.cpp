#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 16;
struct pt {
  int t, w;
  bool operator<(pt a) const {
    if (t != a.t) return t > a.t;
    return w > a.w;
  }
} s[N];
int n, W, best, u[N];
void go(int t, int w, int i) {
  int j;
  for (j = i - 1; j >= 0 && !u[j]; --j);
  if (t + (j >= 0? s[j].t: 0) >= best) return;
  for (; i < n; ++i)
    if (u[i] && s[i].w <= w) break;
  if (i >= n) {
    for (i = 0; i < n && !u[i]; ++i);
    if (i >= n) {
      best = min(t, best);
      return;
    }
    u[i] = 0;
    go(t + s[i].t, W - s[i].w, i+1);
    u[i] = 1;
    return;
  }
  if (i < n) {
    u[i] = 0;
    go(t, w - s[i].w, i+1);
    u[i] = 1;
  }
  go(t, w, i+1);
}
main() {
  int i;
  while (scanf("%d %d", &W, &n) == 2) {
    for (i = best = 0; i < n; ++i) {
      scanf("%d %d", &s[i].t, &s[i].w);
      best += s[i].t;
      u[i] = 1;
    }
    sort(s, s + n);
    go(0, 0, n);
    printf("%d\n", best);
  }
}
