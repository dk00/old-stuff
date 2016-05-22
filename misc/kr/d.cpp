#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1300;
struct pt {
  int x, y, t;
  bool operator<(pt a) const { return t < a.t; }
} t[N];
struct px {
  int x, y;
  bool operator<(px a) const {
    int t0 = t[x].t + y, t1 = t[a.x].t + a.y;
    return t0 < t1;
  }
} o[N*30];
int s[N][30];
inline int dis(pt a, pt b) {
  return 9 * (abs(a.x-b.x) + abs(a.y-b.y));
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, l, q, r, hit, n, m, best = 0;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d %d %d", &t[i].x, &t[i].y, &t[i].t);
      t[i].t *= 10;
    }
    sort(t, t+n);
    pt st;
    st.x = st.y = 1;
    for (i = m = 0; i < n; ++i)
      for (j = 0; j < 28; ++j) {
        for (q = 0; q < 100; ++q)
          s[q][i][j] = 0;
        o[m++] = (px){i, j};
        if (dis(st, t[i]) + 1 <= j)
          best = s[i][j] = 1;
      }
    sort(o, o+m);
    for (int p = 0; p < m; ++p) {
      i = o[p].x, j = o[p].y;
      for (q = 0; q < 100; ++q) {
        for (k = 0; k < n; ++k) {
          if (k == i || eq(q, t[k])) continue;
          r = add(q, t[k]);
          l = t[i].t + j + dis(t[i], t[k]) + 1 - t[k].t;
          if (l < 0) l = 0;
          if (l <= 27 && s[q][i][j] + 1 > s[r][k][l]) {
            s[r][k][l] = s[q][i][j] + 1;
            if (s[q][i][j] + 1 > best)
              best = s[q][i][j] + 1;
          }
        }
      }
    }
    printf("%d\n", best);
  }
}
