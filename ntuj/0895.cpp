#include<cstdio>
const int N = 99;
char u[N], c[N][N];
int n, C, cv[N][N];
long long min;
void MinNode() {
  int i, j;
  long long cost;
  for (i = 0; i < n; ++i){
    u[i] = 0;
    for (j = 1; j < 3; ++j)
      if(cv[i][j] < cv[i][u[i]])
        u[i] = j;
  }
  for (i = cost = 0; i < n; ++i) {
    cost += cv[i][u[i]];
    for ( j = 0 ; j < i; ++j)
      if (c[i][j])
        cost += 1ll*(u[i] - u[j])*(u[i] - u[j])*C;
  }
  if (cost < min) min = cost;
}
void MinEdge() {
  int i, j;
  long long cost;
  for (j = 0; j < 3; ++j) {
    for (i = cost = 0; i < n; ++i)
      cost += cv[i][j];
    if (cost < min) min = cost;
  }
}
void go (int v, long long cost) {
  if (v >= n) {
    if (cost < min) min = cost;
    return;
  }
  if (cost >= min) return;
  int i, j, k, o[3];
  long long nc[3];
  for (i = 0; i < 3; ++i) {
    o[i] = i;
    nc[i] = cv[v][i];
    for (j = 0; j < v; ++j)
      if(c[v][j]) nc[i] += C*1ll*(u[j] - i)*(u[j] - i);
  }
  for (j = 0; j < 2; ++j)
    for (i = 1; i < 3; ++i)
      if (nc[o[i]] < nc[o[i-1]])
        o[i] ^= o[i-1] ^= o[i] ^= o[i-1];
  for (i = 0; i < 3; ++i) {
    u[v] = o[i];
    go (v + 1, cost + nc[o[i]]);

  }
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k;
    scanf("%d %d", &n, &C);
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j)
        c[i][j] = 0;
      scanf("%d %d %d", &cv[i][0], &cv[i][1], &cv[i][2]);
    }
    scanf("%d", &k);
    while (k--) {
      scanf("%d %d", &i,&j);
      c[i-1][j-1] = c[j-1][i-1] = 1;
    }
    min = 2147483647;
    MinNode();
    MinEdge();
    go(0, 0);
    printf("%lld\n", min);
  }
}
