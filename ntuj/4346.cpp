#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
const int N = 30000, inf = 2000000000;
int d[N], u[N];
struct edge {
  int t, c;
};
vector<edge> c[N], c1[N];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, n, m, st, ed, q;
    scanf("%d %d %d %d %d", &n, &m, &q, &st, &ed);
    --st, --ed;
    for (i = 0; i < n; ++i) {
      u[i*2] = u[i*2+1] = 1;
      d[i*2] = d[i*2+1] = inf;
      c[i].clear();
      c1[i].clear();
    }
    while (m--) {
      scanf("%d %d %d", &i, &j, &k);
      --i, --j;
      c[i].push_back((edge){j, k});
    }
    while (q--) {
      scanf("%d %d %d", &i, &j, &k);
      --i, --j;
      c1[i].push_back((edge){j, k});
      c1[j].push_back((edge){i, k});
    }
    queue<int> Q;
    Q.push(st*2);
    d[st*2] = 0;
    while (!Q.empty()) {
      i = Q.front();
      printf("%d %d %d\n", i/2, i%2, d[i]);
      u[i] = 1;
      Q.pop();
      for (k = 0; k < c[i/2].size(); ++k) {
        j = c[i/2][k].t*2 + i%2;
        int nd = d[i] + c[i/2][k].c;
        if (nd < d[j]) {
          if (u[j]) Q.push(j);
          d[j] = nd;
        }
      }
      if (i%2 == 1) continue;
      for (k = 0; k < c1[i/2].size(); ++k) {
        j = c1[i/2][k].t*2 + 1;
        int nd = d[i] + c1[i/2][k].c;
        if (nd < d[j]) {
          if (u[j]) Q.push(j);
          d[j] = nd;
        }
      }
    }
    if (d[ed*2+1] < d[ed*2]) d[ed*2] = d[ed*2+1];
    printf("%d\n", d[ed*2]);
  }
}
