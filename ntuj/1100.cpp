/*
PROB: feed
LANG: C++
 */
#include<stack>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 600, M = 10007;
typedef long long num;
const num inf = 1ll<<62;
int p[M];
num s[M];
struct pt {
  int x, v, c;
  bool operator<(pt a) const {return x < a.x;}
} f[N];
inline num Cost(int p, int q, pt a) {
  return s[p] + (q*q - p*p)*1ll*a.x + (q-p)*1ll*a.c;
}
void Select(int st, int ed, int lb, int ub, pt a) {
  if (st > ed) return;
  int i, j, mid = (st + ed)/2;
  num cost, best = inf;
  p[mid] = -1;
//  lb = 0, ub = mid;
  i = lb-500;
  if (i < 0) i = 0;
  if (lb < mid - a.v) i = mid - a.v;
  for (; i <= ub+500 && i <= mid; ++i) {
    if (s[i] >= inf) continue;
    cost = Cost(i, mid, a);
    if (cost < best) {
      best = cost;
      p[mid] = i;
    }
  }
  Select(st, mid-1, lb, p[mid], a);
  Select(mid+1, ed, p[mid], ub, a);
}
main() {
/*  freopen("feed.in", "r", stdin);
  freopen("feed.out", "w", stdout);*/
  int i, j, n, m, ed;
  while (scanf("%d %d %d", &m, &ed, &n) == 3) {
    for (i = 0; i < n; ++i)
      scanf("%d %d %d", &f[i].x, &f[i].v, &f[i].c);
    sort(f, f+n);
    for (i = 0; i < n; ++i)
      f[i].x = ed - f[i].x;
    for (i = 0; i <= m; ++i)
      s[i] = inf;
    s[0] = 0;
    for (i = 0; i < n; ++i) {
      Select(0, m, 0, m, f[i]);
      for (j = m; j >= 0; --j) {
        if (p[j] < 0) continue;
        s[j] = Cost(p[j], j, f[i]);
      }
    }
    printf("%lld\n", s[m]);
  }
}
