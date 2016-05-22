#include<cstdio>
const int N = 3001;
char t[N];
int C = 1, u[N][N], s[N][N];
inline int go(int x, int y) {
  if (u[x][y] == C) return s[x][y];
  u[x][y] = C;
  if (x == y) return s[x][y] = 1;
  int i;
  s[x][y] = 1 + go(x+1, y);
  i = 1 + go(x, y-1);
  if (i < s[x][y]) s[x][y] = i;
  if (t[x] == t[y]) {
    i = 1 + go(x+1, y-1);
    if (i < s[x][y]) s[x][y] = i;
  }
  return s[x][y];
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, n, m;
    scanf("%s", t);
    for (m = 0; t[m]; ++m);
    for (i = n = 1; t[i]; ++i)
      if (t[i] != t[n-1])
        t[n++] = t[i];
    printf("Case #%d: %d\n", C++, m + 2*go(0, n-1));
  }
}
