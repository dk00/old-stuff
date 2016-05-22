#include<stdio.h>
#define N 5000
int m[N][N], s[N];
int main() {
  int i, j, sum;
  #pragma omp parallel for
  for (i = 0; i < N; i++) {
    sum = 0;
    for (j = 0; j < N; j++) {
      m[i][j] = i + j;
      sum += m[i][j];
    }
    s[i] = sum;
  }
  for (i = 0; i < N; ++i)
    printf("%d %d\n", i, s[i]);
  return 0;
}
