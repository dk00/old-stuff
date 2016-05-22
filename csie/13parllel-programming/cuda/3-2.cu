#include<cuda.h>
#include<stdio.h>
#include<stdlib.h>

int N;
__global__ void add(int N, int s[]) {
  int i, j;
  i = threadIdx.x;
  s[i] = i;
  for (j = 1<<30; j >= N; j >>= 1);
  for (; j > 0; j >>= 1) {
    if (i < j && i+j < N)
      s[i] += s[i+j];
    __syncthreads();
  }
}

main() {
  int *host, *dev;

  scanf("%d", &N);
  //dim3 blocks(Y, Z);
  host = (int *)malloc(N*sizeof(host[0]));
  cudaMalloc((void **)&dev, N*sizeof(dev[0]));
  //cudaMemcpy(dev, host, X*Y*Z*sizeof(dev[0]), cudaMemcpyHostToDevice);
  add <<< 1, N >>> (N, dev);
  cudaMemcpy(host, dev, N*sizeof(dev[0]), cudaMemcpyDeviceToHost);
  printf("%d\n", host[0]);
}

