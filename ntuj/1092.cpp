#include<cstdio>
#include<algorithm>
using namespace std;
struct pt {
  int t, v;
  bool operator<(pt a) const { return t < a.t; }
};
main() {
  while (scanf("%d %d %d", &n, &m, &ed) == 3) {
    for (i = 0; i < n; ++i) {
      scanf("%s %d", tmp, t+i);
      if (i) {
        u[i-1] = 0;
        s[i-1].t = t[i] - t[i-1];
        if (tmp[0] == '+') s[i].v = 1;
        else s[i-1].y = -1;
      }
      --n;
      sort(s, s+n);
      for (i = 0; i < n; ++i) {
        if (i && u[i]) {
          d[i] += d[j];
        } else  {
          u[i] = 1;
          d[i] = s[i].v;
          if (d[i] > 0) {
            lb[i] = 0, lv[i] = 0;
            ub[i] = m - 1, uv[i] = m;
          }
          else {
            lb[i] = 1, lv[i] = 0;
            ub[i] = m, uv[i] = m;
          }
        }
      }
    }
  }
}
