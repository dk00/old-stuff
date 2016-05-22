#include<omp.h>
#include<cstdio>
main() {
  int i, n = 16;
  //#pragma omp parallel for
  #pragma omp parallel
  printf("Hello, world.\n");
  

}
