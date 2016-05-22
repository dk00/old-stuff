#include<vector>
#include<cstdio>
using namespace std;
const int N = 2555;
vector<int> c[N];
int un, u[N], p[N];
int find(int v) {
  return v == p[v]? v: p[v] = find(p[v]);
}
int uni(int a, int b) {
  p[find(a)] = p[find(b)];
}
int go (int v) {
  if (u[v] == un) return 0;
  u[v] = un;
  int sum = 1;
  for (int i = 0; i < c[v].size(); ++i)
    sum += go(c[v][i]);
  return sum;
}
main() {
  int i, j, n, m, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
      c[i].clear();
    while (m--) {
      scanf("%d %d", &i, &j);
      --i, --j;
      c[i].push_back(j);
    }
    for (i = m = 0; i < n; ++i) {
      ++un;
      m += go(i) - 1;
    }
    printf("%d\n", m);
  }
}
