#include<cmath>
#include<cstdio>
const int N = 10001;
const double lg2 = log(2)/log(10);
int num[N][11];
main() {
  int i, j;
  num[0][1] = 1;
  for (i = 1; i < N; ++i) {
    j = floor(pow(10, lg2 * i - floor(lg2 * i)) + 1e-12);
    num[i][j] = 1;
  }
  for (i = 1; i < N; ++i)
    for (j = 1; j < 10; ++j)
      num[i][j] +=num[i-1][j];
  while (scanf("%d", &i) == 1 && i >= 0) {
    printf("%d", num[i][1]);
    for (j = 2; j < 10; ++j)
      printf(" %d", num[i][j]);
    puts("");
  }
}
