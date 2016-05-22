#include<queue>
#include<cstdio>
using namespace std;
const int N = 500000;
int p[N], v[N], dg[N], m0[N], m1[N];
inline int go(int v, int i) {
  if (v > m0[i]) {
    m1[i] = m0[i];
    m0[i] = v;
  }
  else if (v > m1[i]) m1[i] = v;
}
main() {
  int i, n, best;
  while (scanf("%d", &n) > 0 && n) {
    for (i = 0; i < n; ++i) dg[i] = m0[i] = m1[i] = 0;
    for (i = 1; i < n; ++i) {
      scanf("%d %d", p+i, v+i);
      ++dg[p[i]];
    }
    queue<int> Q;
    for (i = 0; i < n; ++i)
      if (dg[i] == 0) Q.push(i);
    best = 0;
    while (!Q.empty()) {
      i = Q.front();
      Q.pop();
      if (m0[i] + m1[i] > best) best = m0[i] + m1[i];
      if (--dg[p[i]] == 0) Q.push(p[i]);
      go(v[i] + m0[i], p[i]);      
    }
    printf("%d\n", best);
  }
}
