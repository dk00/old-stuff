#include<math.h>
#include<stdio.h>
int main() {
  int i;
  double v = 0.0;
  #pragma omp parallel for firstprivate(v) lastprivate(v)
  for (i = 0; i < 1000000000; i++) {
    v += sqrt(i);
  }
  printf("%lf\n", v);
  return 0;
}
