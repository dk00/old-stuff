#include<stdio.h>
#define N 5000
int m[N][N];
int main() {
  int i, j, sum;
  for (i = 0; i < N; i++) {
    sum = 0;
    for (j = 0; j < N; j++) {
      m[i][j] = i + j;
      sum += m[i][j];
    }
    printf("%d %d\n", i, sum);
  }
  return 0;
}
