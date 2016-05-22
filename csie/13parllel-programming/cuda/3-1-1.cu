#include<cuda.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

int N;
__global__ void add(int N, int s[]) {
  int i, j;
  i = threadIdx.x;
  s[i] = i;
  for (j = 2; j <= N; j <<= 1) {
    if (i%j == 0)
      s[i] += s[i+j/2];
    __syncthreads();
  }
}

main() {
  int *host, *dev;
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  scanf("%d", &N);
  //dim3 blocks(Y, Z);
  host = (int *)malloc(N*sizeof(host[0]));
  cudaMalloc((void **)&dev, N*sizeof(dev[0]));
  //cudaMemcpy(dev, host, X*Y*Z*sizeof(dev[0]), cudaMemcpyHostToDevice);
  clock_t t = clock();
  float t0;
  cudaEventRecord(start, 0);
  add <<< 1, N >>> (N, dev);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&t0, start, stop);
  t = clock() - t;
  printf("%d %f\n", t, t0);
  cudaMemcpy(host, dev, N*sizeof(dev[0]), cudaMemcpyDeviceToHost);
  printf("%d\n", host[0]);
}

