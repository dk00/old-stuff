#include<cuda.h>
#include<stdio.h>

#ifndef X
#define X 8
#endif

__global__ void multiply(int s[]) {
  s[threadIdx.x] *= threadIdx.x;
}

main() {
  int i, host[X], *dev;
  for (i = 0; i < X; i++)
    host[i] = i;
  cudaMalloc((void **)&dev, X*sizeof(dev[0]));
  cudaMemcpy(dev, host, X*sizeof(dev[0]), cudaMemcpyHostToDevice);
  multiply <<< 1, X/2 >>> (dev);
  cudaMemcpy(host, dev, X*sizeof(dev[0]), cudaMemcpyDeviceToHost);
  for (i = 0; i < X; i++)
    printf("%d\n", host[i]);
}

