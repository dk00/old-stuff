#include<math.h>
#include<stdio.h>
#define N 1000000
int main() {
  int i;
  double x, area = 0;
  #pragma omp parallel for private(x)
  for (i = 0; i < N; i++) {
    x = (i + .5) / N;
    x = 4 / (1 + x*x);
    #pragma omp critical
    area += x;
  }
  printf("%.10lf\n", area/N);
  return 0;
}
