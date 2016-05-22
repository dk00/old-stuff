#include<queue>
#include<cstdio>
using namespace std;
const int N = 111;
int n, un, c[N][N], u[N], p[N], d[N];
int sp() {
  int i, j;
  for (i = 0; i < n; ++i) d[i] = n;
  for (i = 0; i < n; ++i) {
    if (d[i] < n) continue;
    d[i] = 0;
    queue<int> Q;
    Q.push(i);
    ++un;
    while (!Q.empty()) {
      i = Q.front();
      Q.pop();
      u[i] = un;
      for (j = 0; j < n; ++j) {
        if (u[i] == u[j] && d[i] == d[j] && c[i][j]) break;
        if (c[i][j] && d[i] + 1 < d[j]) {
          d[j] = d[i] + 1;
          p[j] = i;
          Q.push(j);
        }
      }
      if (j < n) {
        int r = 0;
        while (i != j) {
          i = p[i];
          j = p[j];
          ++r;
        }
        return r*2 + 1;
      }
    }
  }
  return 0;
}
main() {
  int i, j, k;
  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        scanf("%d", &c[i][j]);
    printf("%d\n", sp());
  }
}
