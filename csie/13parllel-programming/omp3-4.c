#include<stdio.h>

#ifndef N
#define N 500
#endif

int a[N][N], b[N][N], c[N][N];

int main() {
  int i, j, k, sum;
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      int i, j;
      for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
          a[i][j] = i + j;
    }
    #pragma omp section
    {
      int i, j;
      for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
          b[j][i] = i - j;
    }
  }

  #pragma omp parallel for private(j, k)
  for (i = 0; i < N; i++)
    for (k = 0; k < N; k++)
      for (j = 0; j < N; j++)
        c[i][j] += a[i][k] * b[j][k];

  sum = 0;
  #pragma omp parallel for reduction(+:sum) private(j)
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      sum += c[i][j];

  printf("%d\n", sum);
  return 0;
}

