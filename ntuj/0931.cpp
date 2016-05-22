#include<map>
#include<queue>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 20012;
map<int, int> c;
//vector<int> to[N];
queue<int> to[N];
inline int& Cap(int a, int b) {return c[a*N + b];}
int t, n, m, p[N];
void Init(int d) {
  int i, j, k;
  c.clear();
  for (i = 0; i < n; ++i)
    Cap(0, i+1) = d;
  for (i = 0; i < m; ++i)
    Cap(n+i+1, t) = 1;
  for (i = 1; i <= n; ++i)
    for (j = 0; j < to[i].size(); ++j) {
      k = to[i].front();
      to[i].pop();
      to[i].push(k);
      Cap(i, k) = 1;
    }
}
void Add(int x, int a, int b) {
  to[a].push(n+x+1);
  to[b].push(n+x+1);
  to[n+x+1].push(a);
  to[n+x+1].push(b);  
}
int go(int v) {
  if (v == t) return 1;
  if (p[v]) return 0;
  p[v] = 1;
  for (int j = 0; j < to[v].size(); ++j) {
    int i = to[v].front();
    to[v].pop();
    to[v].push(i);
    if (Cap(v, i)-- && go(i))
      return ++Cap(i, v);
    else ++Cap(v, i);
  }
  return 0;
}
int flow() {
  int i, f = 0, tmp;
  while(1) {
    for (i = 0; i <= t; ++i)
      p[i] = 0;
    if (!go(0)) break;
    do {
      ++f;
      p[0] = 0;
    } while (go(0));
  }
  return f;
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, x;
    scanf("%d %d", &n, &m);

    t = n + m + 1;
    for (i = 0; i <= t; ++i)
      while (!to[i].empty()) to[i].pop();
    for (i = 0; i <= n; ++i)
      to[0].push(i+1);
    for (i = 0; i <= m; ++i)
      to[n+i+1].push(t);
    for (i = 0; i < m; ++i) {
      scanf("%d %d", &j, &k);
      Add(i, j, k);
    }

    for (i = (m + n - 1)/n, j = (m + 1)/2; i <= j;) {
      k = (i + j)/2;
      Init(k);
      if (flow() >= m) x = k, j = k - 1;
      else i = k + 1;      
    }
    printf("%d\n", x);
  }
}
