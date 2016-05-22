#include<cuda.h>
#include<stdio.h>

#ifndef X
#define X 8
#endif

__global__ void multiply(int s[]) {
  s[threadIdx.x] *= threadIdx.x;
}

main() {
  int i, s[X];
  for (i = 0; i < X; i++)
    s[i] = i;
  multiply <<< 1, X >>> (s);
  for (i = 0; i < X; i++)
    printf("%d\n", s[i]);
}

