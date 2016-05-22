#include<stdio.h>
int main() {
  int i;
  #pragma omp parallel for
  for (i = 0; i <= 15; i++) {
    if (omp_get_thread_num() == 0) {
      printf("%d\n", omp_get_num_procs());
      printf("%d\n", omp_get_num_threads());
    }
  }
  return 0;
}
