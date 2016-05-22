#include<map>
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
const int N = 30000, inf = 2000000000;
int t, p[N], d[N];
vector<int> to[N];
map<int,int> Cap[N];

inline void sp() {
  int i, j, k;
  for (i = 0; i <= t; ++i) d[i] = inf;
  queue<int> Q;
  Q.push(0);
  d[0] = 0;
  while (d[t] >= inf && !Q.empty()) {
    j = Q.front();
    Q.pop();
    for (i = 0; i < to[j].size(); ++i) {
      k = to[j][i];
      if (d[j] + 1 < d[k] && Cap[j][to[j][i]]) {
        d[k] = d[j] + 1;
        Q.push(k);
      }
    }
  }
}
inline int go(int v) {
  if (v == t) return 1;
  if (p[v]) return 0;
  p[v] = 1;
  int sum = 0;
  for (int i = 0; i < to[v].size(); ++i) {
    int j = to[v][i];
    if (d[v]+1 > d[j]) continue;
    if (Cap[v][j]-- && go(j)) {
      ++Cap[j][v];
      if (v > 0) return 1;
      ++sum;
    }
    else ++Cap[v][j];
  }
  return sum;
}
inline int flow() {
  int i, f = 0, tmp;
  while (1) {
    sp();
    for (i = 0; i <= t; ++i) p[i] = 0;
    if (!(tmp=go(0))) break;
    f += tmp;
  }
  return f;
}
inline void add(int a, int b, int c = 1) {
  to[a].push_back(b);
  to[b].push_back(a);
  Cap[a][b] = c;
}
struct ed {
  int x, y;
}s[N];
vector<int> right[N];
main() {
  int i, j, n, m;
  while (scanf("%d", &n) == 1 && n) {
    for (i = m = 0; i < n; ++i) {
      scanf("%d", &j);
      while(j--) {        
        scanf("%d", &s[m].y);
        --s[m].y;
        s[m++].x = i;
      }
      right[i].clear();      
    }
    t = n + 2*m + 1;    
    for (i = 0; i <= t ; ++i)
      to[i].clear(),Cap[i].clear();;
    for (i = 0; i < m; ++i) {
      add(0, n+i+1);
      add(n+m+i+1, t);
      add(n+i+1, s[i].y+1);
      add(s[i].x+1, n+m+i+1);
      add(s[i].x+1, s[i].y+1, m+1);
    }
    printf("%d\n", m - flow());
    for (i = 0; i < m; ++i) {
      if (Cap[n+m+i+1][s[i].x+1])
        right[s[i].x].push_back(i);
      for (int k = 0; k < Cap[s[i].y+1][s[i].x+1]; ++k)
        right[s[i].x].push_back(m+s[i].y);
    }
    for (i = 0; i < m; ++i) {
      if (!Cap[n+m+i+1][t]) continue;
      printf("%d", s[i].x+1);
      for (j = i; Cap[s[j].y+1][n+j+1]; ) {
        printf(" %d", s[j].y+1);
        int k = s[j].y;
        j = right[s[j].y].back();
        right[k].pop_back();
        while (j >= m) {
          printf(" %d", j-m+1);
          k = j - m;
          if (right[k].size() < 1) {
            return 0;
          }
          j = right[k].back();
          right[k].pop_back();
        }
      }
      printf(" %d\n", s[j].y+1);
    }
  }
}
