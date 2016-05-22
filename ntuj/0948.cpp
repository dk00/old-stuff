#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 20012, inf = 2000000000;
int p[N], f[N], t[N], s[N], dg[N];
int main() {
  int i, j, n;
  while (scanf("%d", &n) == 1 && n) {
    fill(dg, dg+n, 0);
    fill(s, s+n, inf);
    for (i = 0; i < n; ++i) {
      scanf("%d %d %d", p+i, f+i, t+i);
      ++dg[--p[i]];
    }
    queue<int> Q;
    for (i = 0; i < n; ++i)
      if (dg[i] == 0) {
        s[i] = 0;
        Q.push(i);
      }
    while (!Q.empty()) {
      i = Q.front();
      Q.pop();
      if (p[i] < 0) continue;
      j = (t[i] + s[i])*2 + !f[i];
      if (j < s[p[i]]) s[p[i]] = j;
      if (!--dg[p[i]]) Q.push(p[i]);
    }
    for (i = 0; p[i] >= 0; ++i);
    printf("%d\n", s[i] + t[i]);
  }
}
