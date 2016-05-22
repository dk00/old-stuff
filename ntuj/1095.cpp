#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1600;
int un, u[N][N];
struct pt {
  int x, y, x0, y0;
  bool operator<(pt a)const {
    if (x != a.x) return x < a.x;
    return y < a.y;
  }
} s[N], t[N];
bool cmp(pt a, pt b) {
  return a.x*1ll*b.y > a.y*1ll*b.x || a.x*1ll*b.y==a.y*1ll*b.x && a.x < b.x;
}
main() {
  int i, j, k, a, n, m;
  while (scanf("%d", &n) == 1 && n) {
    long long ans = 0;
    ++un;
    for (i = 0; i < n; ++i)
      scanf("%d %d", &s[i].x, &s[i].y);
    sort(s, s+n);
    map<int, int> Hx, Hy;
    for (i = 0; i < n; ++i)
      Hx[s[i].x] = Hx.size() - 1;
    for (i = 0; i < n; ++i)
      s[i].x0 = Hx[s[i].x];
    for (i = 0; i < n; ++i)
      swap(s[i].x, s[i].y);
    sort(s, s+n);
    for(i = 0; i < n; ++i)
      Hy[s[i].x] = Hy.size() - 1;
    for (i = 0; i < n; ++i) {
      s[i].y0 = Hy[s[i].x];
      u[s[i].x0][s[i].y0] = un;
    }
    for (i = 0; i < n; ++i)
      swap(s[i].x, s[i].y);
    for (i = 0; i < n; ++i) {
      for (m = 0, j = i + 1; j < n; ++j) {
        t[m] = s[j];
        t[m].x -= s[i].x;
        t[m].y -= s[i].y;
        if(t[m].y > 0 || t[m].y == 0 && t[m].x > 0)
          ++m;
      }
      sort(t, t+m, cmp);
      for (j = k = 0; j < m; ++j) {
        for (; k < m; ++k) {
          if (t[j].x *1ll* t[k].x + t[j].y *1ll* t[k].y < 0)
            break;
        }
        for (int l = k-1; l >= j && t[j].x *1ll* t[l].x + t[j].y *1ll* t[l].y == 0; --l) {
          pt pp;
          pp.x = t[j].x + t[l].x + s[i].x;
          pp.y = t[j].y + t[l].y + s[i].y;
          if (Hx.count(pp.x) == 0) continue;
          if (Hy.count(pp.y) == 0) continue;
          if (u[Hx[pp.x]][Hy[pp.y]] == un) {
            pp.x -= s[i].x;
            pp.y -= s[i].y;
            long long ret = t[j].x*1ll*pp.y+pp.x*1ll*t[l].y-t[j].y*1ll*pp.x-pp.y*1ll*t[l].x;
            if (ans < ret)
              ans = ret;
          }
        }
      }
    }
    printf("%lld\n", ans/2);
  }
}
