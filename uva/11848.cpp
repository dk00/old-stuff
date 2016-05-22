#include<cmath>
#include<queue>
#include<cstdio>
using namespace std;
const int N = 101;
const long long inf = 1ll<<41;
int n, u[N];
long long c0[N][N], c1[N][N];
long long d[N];
inline long long Cost(int x, int y, long long a) {
  if (c0[x][y] < inf && c1[x][y] < inf)
    return a*c0[x][y] + (10000 - a)*c1[x][y];
  if (c0[x][y] < inf) return 10000*c0[x][y];
  return 10000*c1[x][y];
}
long long sp(long long a) {
  int i, j;
  long long k;
  for (i = 0; i < n; ++i) d[i] = inf, u[i] = 1;
  d[0] = 0;
  queue<int> Q;
  Q.push(0);
  while (!Q.empty()) {
    i = Q.front();
    Q.pop();
    u[i] = 1;
    for (j = 0; j < n; ++j) {
      k = d[i] + Cost(i, j, a);
      if (k < d[j]) {
        d[j] = k;
        if (u[j]) u[j] = 0, Q.push(j);
      }
    }
  }
  return d[n-1];
}
main() {
  int i, j, m1, m2, q;
  while (scanf("%d %d %d %d", &n, &m1, &m2, &q) > 0 && n >= 0) {
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        c0[i][j] = c1[i][j] = inf;
    while (m1--) {
      scanf("%d %d", &i, &j);
      scanf("%lld", &c0[i][j]);
      c0[j][i] = c0[i][j];
    }
    while (m2--) {
      scanf("%d %d", &i, &j);
      scanf("%lld", &c1[i][j]);
      c1[j][i] = c1[i][j];
    }
    while (q--) {
      char tmp[99];
      scanf("%s", tmp);
      for (i = 0; tmp[i] && tmp[i] != '.'; ++i);
      if (tmp[i] == '.') {
        for (j = 1; tmp[i+j] && j <= 4; ++j);
        for (; j <= 4; ++j)
          tmp[i+j] = '0';
        tmp[i+j] = 0;
      }
      i = j = 0;
      sscanf(tmp, "%d.%d" , &i, &j);
      printf("%lld\n", sp(i*10000+j)/10000);
    }
  }
}
