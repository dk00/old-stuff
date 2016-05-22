#include<vector>
#include<cstdio>
using namespace std;
const int N = 55555;
int anc[N], p[N], u[N], pre[N], post[N], s[N];
struct pt { int v, val; };
vector<int> c[N];
vector<pt> q[N];
int find(int v) {
  return v == p[v]? v: p[v] = find(p[v]);
}
void uni(int a, int b) {
  p[find(a)] = find(b);
}
void go(int v, int from) {
  anc[find(v)] = v;
  int i;
  for (i = 0; i < c[v].size(); ++i) {
    if (c[v][i] == from) continue;
    go(c[v][i], v);
    uni(v, c[v][i]);
    anc[find(v)] = v;
  }
  u[v] = 1;
  for (i = 0; i < q[v].size(); ++i) {
    if (!u[q[v][i].v]) continue;
    printf("%d %d: %d\n", v, q[v][i].v, anc[find(q[v][i].v)]);
    pre[anc[find(q[v][i].v)]] += q[v][i].val;
    if (v != anc[find(q[v][i].v)]) post[v] -= q[v][i].val;
    if (q[v][i].v != anc[find(q[v][i].v)]) post[q[v][i].v] -= q[v][i].val;
  }
}
void go(int v, int from, int sum) {
  int i;
  sum += pre[v];
  s[v] = sum;
  sum += post[v];
  for (i = 0; i < c[v].size(); ++i) {
    if (c[v][i] == from) continue;
    go(c[v][i], v, sum);
  }
}
main() {
  int i, j, k, n, m, T, C = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      c[i].clear(), q[i].clear();
    for (k = 1; k < n; ++k) {
      scanf("%d%d", &i, &j);
      c[i].push_back(j);
    }
    scanf("%d", &m);
    while (m--) {
      scanf("%d %d %d", &i, &j, &k);
      q[i].push_back((pt){j, k});
      if (i != j)
        q[j].push_back((pt){i, k});
    }
    for (i = 0; i < n; ++i) {
      u[i] = 0, p[i] = i;
      pre[i] = post[i] = 0;
    }
    go(0, -1);
    go(0, -1, 0);
    for (i = 0; i < n; ++i)
      printf("%d %d\n", pre[i], post[i]);
    printf("Case #%d:\n", C++);
    for (i = 0; i < n; ++i)
      printf("%d\n", s[i]);
  }
}
