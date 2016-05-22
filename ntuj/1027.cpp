#include<cstdio>
const int N = 501;
int t, n, ed, p[N], pn[N], c[N][N], path[N][N];
int go(int v) {
  if (p[v]) return 0;
  if (v == t) return 1;
  p[v] = 1;
  for (int i = 0; i <= t; ++i)
    if (c[v][i]-- && go(i))
      return ++c[i][v];
    else ++c[v][i];
  return 0;
}
int flow() {
  int f = 0, i;
  while (1) {
    for (i = 0; i <= t; ++i) p[i] = 0;
    if (!go(0)) break;
    ++f;
  }
  return f;
}
inline bool valid(int a, int b) {
  return (c[t][b+n+1] && c[a+1][b+n+1] + c[b+n+1][a+1] > 0);
}
int go(int a, int d, int v) {
  if (p[v]) return 0;
  p[v] = 1;
  if (v == ed) return d;
  int i, j;
  for (i = 0; i <= t; ++i) {
    if (!c[v][i]) continue;
    path[a][d] = i;
    if (j = go(a, d+1, i)) return j;
  }      
  return 0;
}
bool find(int a, int b) {
  int i, j, k;
  for (i = 0; i < n; ++i)
    if (c[i+n+1][a+1]) break;
  for (j = 0; j < n; ++j)
    if (c[b+n+1][j+1]) break;
  --c[a+1][b+n+1];
  ed = a + 1;
  for (i = 0; i <= t; ++i)
    p[i] = 0;
  if (!(pn[a] = go(a, 2, b+n+1))) {
    ++c[a+1][b+n+1];
    --c[b+n+1][a+1];    
    return false;
  }
  for (i = 1; i < pn[a]-1; ++i) {
    --c[path[a][i]][path[a][i+1]];
    ++c[path[a][i+1]][path[a][i]];
  }
  return true;
}
void undo(int a) {
  for (int i = 0; i < pn[a]-1; ++i) {
    ++c[path[a][i]][path[a][i+1]];
    --c[path[a][i+1]][path[a][i]];
  }
  ++c[path[a][1]][path[a][0]];
}
int go(int m, int d) {
  if (d >= n) return 1;
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (!valid(d, i)) continue;
    path[d][0] = d+1;
    path[d][1] = i+n+1;
    pn[d] = 2;
    if (c[d+1][i+n+1] && !find(d, i)) continue;
    c[i+n+1][d+1] = 0;
    count += go(m - count, d+1);
    if (count >= m) break;
    undo(d);    
  }
  return count;
}
main() {
  int T, C = 1;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, m;
    scanf("%d %d %d", &n, &m, &k);
    t = n*2 + 1;
    for (i = 0; i <= t; ++i)
      for (j = 0; j <= t; ++j)
        c[i][j] = 0;
    for (i = 0; i < n; ++i) {
      c[0][i+1] = c[i+n+1][t] = 1;
      for (j = 0; j < n; ++j)
        c[i+1][j+n+1] = 1;
    }
    while (m--)
      for (i = 0; i < n; ++i) {
        scanf("%d", &j);
        c[i+1][j+n] = 0;
      }
    m = flow(); 
    printf("Case #%d: ", C++);
    if (m < n || k > go(k, 0)) {
      puts("-1");
      continue;
    }
    for (i = 0; i < n-1; ++i)
      printf("%d ", path[i][1]-n);
    printf("%d\n", path[i][1]-n);
  }
}
