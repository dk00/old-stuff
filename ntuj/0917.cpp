#include<cstdio>
const int N = 55;
int c[N][N];
void Init(int n) {
  int i, j, k;
  for (i = 0; i <= n; ++i)
    for (j = 0; j <= n; ++j)
      c[i][j] = 0;
  c[0][0] = 1;
  for (i = 0; i < n; ++i)
    for (j = 0; j <= n; ++j)
      for



}
main() {
  scanf("%s %d", tmp, &n);
  Init(n);
}
