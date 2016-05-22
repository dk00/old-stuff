#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
const int N = 105, inf = 2000000000;
struct pt {
  int x, y, z;
} s[N];
inline int Dis(pt a, pt b) {
  return (int)ceil(sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z)));
}
int n, xn, p[N], d[N], u[N], x[N], c[N][N], t[N][N];
inline int Cost(int d, int a, int b) {
  if (d < t[a][b]) return Dis(s[a], s[b]);
  return c[a][b];
}
void elim(int v) {
  vector<int> tmp;
  tmp.push_back(v);
  int i, j, k;
  k = v;
  for (j = 0, i = p[v]; ; i = p[i]) {
    j += Cost(d[p[i]], p[i], i);
    if (t[p[i]][i] < t[p[k]][k])
      k = i;
    tmp.push_back(i);
    if (i == v) break;
  }
  j = (d[p[k]] - t[p[k]][k])/j * j;
  for (i = 1; i < tmp.size(); ++i) {
    d[tmp[i]] -= j;
    p[tmp[i]] = -1;
  }
}
void sp() {
  int i, j;
  for (i = 0; i < n; ++i) {
    p[i] = -1;
    u[i] = 1, d[i] = inf;
  }
  d[0] = 0;
  queue<int> Q;
  Q.push(0);
  while (!Q.empty()) {
    i = Q.front();
    Q.pop();    
    u[i] = 1;
    for (++xn, j = i; j >= 0 && x[j] != xn; x[j] = xn, j = p[j]);
    if (j >= 0) elim(j);
    for (j = 0; j < n; ++j)
      if (d[i] + Cost(d[i], i, j) < d[j]) {
        p[j] = i;
        d[j] = d[i] + Cost(d[i], i, j);
        if (u[j]) {
          u[j] = 0;
          Q.push(j);
        }
      }
  }
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, m;
    for (i = 0; i < N; ++i)
      for (j = 0; j < N; ++j)
        t[i][j] = inf;
    scanf("%d %d %d", &s[0].x, &s[0].y, &s[0].z);
    scanf("%d %d %d", &s[1].x, &s[1].y, &s[1].z);
    n = 2;
    scanf("%d", &m);
    for (i = 0; i < m; ++i) {
      scanf("%d %d %d", &s[n].x, &s[n].y, &s[n].z);
      ++n;
      scanf("%d %d %d", &s[n].x, &s[n].y, &s[n].z);
      scanf("%d %d", &t[n-1][n], &c[n-1][n]);
      if (Dis(s[n-1], s[n]) < c[n-1][n])
        c[n-1][n] = Dis(s[n-1], s[n]);
      ++n;
    }
    sp();
    printf("%d\n", d[1]);
  }
}
