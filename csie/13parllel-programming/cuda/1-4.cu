#include<cuda.h>
#include<stdio.h>

#ifndef X
#define X 8
#endif
#ifndef Y
#define Y 8
#endif

__global__ void multiply(int s[]) {
  s[threadIdx.x*Y + threadIdx.y] *= (threadIdx.x + threadIdx.y);
}

main() {
  int i, j, host[X*Y], *dev;
  for (i = 0; i < X; i++)
    for (j = 0; j < Y; j++)
      host[i*Y + j] = i + j;
  dim3 blocks(X, Y);
  cudaMalloc((void **)&dev, X*Y*sizeof(dev[0]));
  cudaMemcpy(dev, host, X*Y*sizeof(dev[0]), cudaMemcpyHostToDevice);
  multiply <<< 1, blocks >>> (dev);
  cudaMemcpy(host, dev, X*Y*sizeof(dev[0]), cudaMemcpyDeviceToHost);
  for (i = 0; i < X*Y; i++)
    printf("%d\n", host[i]);
}

