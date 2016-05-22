#include<map>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1300, dx[] = {3, 1, -3, -1, 0};
struct state {
  int x, t, p0, p1;
  bool operator<(state a) const {
    if (t != a.t) return t > a.t;
    if (x != a.x) return x < a.x;
    if (p0 != a.p0) return p0 < a.p0;
    return p1 < a.p1;
  }
};
int t[9][N], t0[N];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, l, n, best, ub = 0;
    for (i = 0; i < 9; ++i)
      for (j = 0; j <= 1000; ++j)
        t[i][j] = 0;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d %d %d", &j, &k, &t0[i]);
      t0[i] *= 10;
      if (t0[i] + 27 > ub) ub = t0[i] + 27;
      --j, --k;
      for (l = 0; l < 28; ++l)
        t[j*3 + k][t0[i] + l] = i + 1;
    }
    state a;
    a.x = a.t = a.p0 = a.p1 = 0;
    map<state, int> s;
    priority_queue<state> Q;
    s[a] = 0;
    Q.push(a);
    best = 0;
    state c;
    while (!Q.empty()) {
      a = Q.top();
      Q.pop();
      if (a.t > ub) continue;
      j = s[a];
      if (a.p0 > 0 && t0[a.p0 - 1] + 27 < a.t) a.p0 = 0, a.p0 = a.p1;
      if (a.p0 > 0 && t0[a.p0 - 1] + 27 < a.t) a.p0 = 0;
      if (t[a.x][a.t+1] && t[a.x][a.t+1] != a.p0 && t[a.x][a.t+1] != a.p1) {
        state b = a;
        ++b.t;
        if (b.p1) {
          b.p0 = b.p1;
          b.p1 = t[a.x][a.t+1];
        }
        else if (b.p0) {
          b.p1 = t[a.x][a.t+1];
        }
        else b.p0 = t[a.x][a.t+1];
        if (s.count(b) == 0) Q.push(b);
        if (j + 1 > s[b]) s[b] = j + 1;
        if (j + 1 > best) best = j + 1, c = b;
      }
      state b = a;
      if (b.t%10 == 9) b.t += 10;
      else b.t += 9 - b.t%10;
      if (s.count(b) == 0) Q.push(b);
      if (j > s[b]) s[b] = j;
      for (i = 0; i < 4; ++i) {
        state b = a;
        b.x = a.x + dx[i];
        if (b.x < 0 || b.x >= 9) continue;
        b.t += 9;
        if (!s.count(b)) Q.push(b);
        if (j > s[b]) s[b] = j;
      }
    }
    printf("%d\n", best);
  }
}
