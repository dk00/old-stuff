#include<cstdio>
const int N = 11;
int s[N][N];
main() {
  long long i, j, k, sum, T;
  for (i = 0; i < N; ++i) {
    s[i][0] = 1;
    for (j = 1; j < N; ++j)
      s[i][j] = (s[i][j-1] * i)%10;
  }
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld %lld %lld", &k, &i, &j);
    k %= 10;
    for (sum = 0;i <= j; ++i) {
      if (i > 0 && (j - i)/4 > 1 && i % 4 == 1) {
        sum += (j - i)/4 % 10 * (s[k][1] + s[k][2] + s[k][3] + s[k][4]);
        sum %= 10;
        i += (j - i)/4*4;
      }
      sum += s[k][4*!!i+i%4];
      sum %= 10;
    }
    printf("%lld\n", sum);
  }
}
