#include<cstdio>
const int N = 1001, M = 10056;
int s[N][N];
main() {
  int i, j, T;
  for (i = 0; i < N; ++i)
    s[i][0] = 0, s[i][1] = i;
  for (i = 1; i < N; ++i)
    for (j = 2; j <= i; ++j)
      s[i][j] = (s[i-1][j] + s[i-1][j-1])%M;
  s[0][0] = 1;
  for (i = 1; i < N; ++i)
    for (j = 1; j <= i; ++j) {
      s[i][0] += s[i][j]*s[i-j][0];
      s[i][0] %= M;
    }

  scanf("%d", &T);
  while (T--) {
    scanf("%d", &i);
    printf("%d\n", s[i][0]);
  }
}
