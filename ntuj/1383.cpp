#include<cstdio>
const int N = 16;
int s[N][1<<N], pow[N][1<<N], lim[1<<N];
main() {
  int i, j, k, n, m, r, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &r);
    m = 1 << n;
    for (i = 0; i < m; ++i) {
      scanf("%d", lim+i);
      s[0][i] = i;
      pow[0][i] = lim[i];
    }
    for (i = 0; i < n; ++i) {
      for (j = 0; j < m; j += (2<<i)){
        k = j + (1<<i);
        pow[i+1][j] = pow[i][j] - pow[i][k];
        if (pow[i+1][j] < 0)
          pow[i+1][j] = -pow[i+1][j];
        pow[i+1][j] += r;
        if (pow[i][j] >= pow[i][k])
          s[i+1][j] = s[i][j];
        else
          s[i+1][j] = s[i][k];
        if (pow[i+1][j] > lim[s[i+1][j]])
          pow[i+1][j] = lim[s[i+1][j]];
      }
    }
    printf("%d\n", s[i][0] + 1);
    j = s[i][0];
    for (i = 0; i < n; ++i) {
      if (i) printf(" ");
      printf("%d", s[i][j^(1<<i)] + 1);
      j &= ~(1<<i);
    }
    puts("");
  }
}
