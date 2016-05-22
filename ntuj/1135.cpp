#include<queue>
#include<cstdio>
using namespace std;
const int N = 1005, inf = 2000000000;
int n, n0, t, sum, p[N], d[N], u[N], cap[N][N], cost[N][N], c[N][N];
inline int Cost(int a, int b) {
  return cost[a][b] - cost[b][a];
}
inline int sp(int st) {
  int i, j, k;
  for (i = 0; i < n*2; ++i)
    d[i] = inf, u[i] = 0;
  d[st] = 0;
  queue<int> Q;
  Q.push(st);
  while (!Q.empty()) {
    i = Q.front(), Q.pop();
    u[i] = 0;
    for (j = 0; j < n*2; ++j) {
      if (cap[i][j] < 1) continue;
      k = d[i] + Cost(i, j);
      if (k < d[j]) {
        d[j] = k, p[j] = i;
        if (!u[j])
          u[j] = 1, Q.push(j);
      }
    }
  }
}
int s[8], g[8];
void Init() {
  int i, j;
  for (i = 0; i <= t; ++i)
    for (j = 0; j <= t; ++j)
      cap[i][j] = 0;
  for (i = 0; i < n; ++i) {
    cap[i][i+n] = 1;
    for (j = 0; j < n; ++j)
      if (c[i][j])
        cap[i+n][j] = 1;
  }
}

main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, m;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        c[i][j] = 0;
    while (m--) {
      scanf("%d %d", &i, &j);
      c[i][j] = c[j][i] = 1;
    }
    scanf("%d", &n0);
    for (i = 0; i < n0*2; ++i)
      s[i] = 0, scanf("%d", &g[i]);
    t = n*2 + 1;
    for (i = 0; i <= t; ++i)
      for (j = 0; j <= t; ++j)
        cost[i][j] = 0;
    for (i = sum = 0; i < n; ++i) {
      scanf("%d", &cost[i][i+n]);
      sum += cost[i][i+n];
    }
    for (i = 0; i < n0*2; ++i) {
      if (s[i]) continue;
      s[i] = 1;
      Init();
      sp(g[i]);
      for (j = i+1; s[j]; ++j);
      for (k = j; j < n0*2; ++j)
        if (d[g[j]+n] < d[g[k]+n]) k = j;
      if (d[g[k]+n] >= inf) {
        sum = -1;
        break;
      }
      sum -= d[g[k]+n];
      s[k] = 1;
      for (k = g[k]+n; k != g[i]; k = p[k])
        --cap[p[k]][k], ++cap[k][p[k]];
    }
    printf("%d\n", sum);
  }
}
