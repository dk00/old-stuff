#include<queue>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2012;
int t, p[N], c[N][N];
int go(int v) {
  if (v == t) return 1;
  if (p[v]) return 0;
  p[v] = 1;
  for (int i = 0; i <= t; ++i)
    if (c[v][i]-- && go(i))
      return ++c[i][v];
    else ++c[v][i];
  return 0;
}
int flow() {
  int i, f = 0;
  while (1) {
    for (i = 0; i <= t; ++i) p[i] = 0;
    if (!go(0)) break;
    ++f;
  }
  return f;
}
int main() {
  int i, j, k, n, m;
  while (scanf("%d %d", &n, &m) == 2) {
    t = n + 1202;
    for (i = 0; i <= t; ++i)
      for (j = 0; j <= t; ++j)
        c[i][j] = 0;
    for (i = 0; i < n; ++i) {
      scanf("%d %d", &j, &k);
      k += j;
      for (; j < k; ++j)
        ++c[i+1][j+n+1];
      c[0][i+1] = 2;
    }
    for (i = 0; i < 1202; ++i)
      c[i+n+1][t] = m;
    if (flow() != n*2) {
      puts("No");
      continue;
    }
    puts("Yes");
    for (i = 0; i < n; ++i) {
      for (j = 0; !c[j+n+1][i+1]; ++j);
      printf("%d", j);
      for (j++; !c[j+n+1][i+1]; ++j);
      printf(" %d\n", j);
    }
  }
}
