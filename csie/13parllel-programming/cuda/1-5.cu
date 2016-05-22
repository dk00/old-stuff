#include<cuda.h>
#include<stdio.h>

#ifndef X
#define X 3
#endif
#ifndef Y
#define Y 3
#endif
#ifndef Z
#define Z 3
#endif

__global__ void multiply(int s[]) {
  s[blockIdx*Y*Z + threadIdx.x*Z + threadIdx.y] = blockIdx*Y*Z + threadIdx.x*Z + threadIdx.y;
}

main() {
  int i, host[X*Y*Z], *dev;

  dim3 blocks(Y, Z);
  cudaMalloc((void **)&dev, X*Y*Z*sizeof(dev[0]));
  cudaMemcpy(dev, host, X*Y*Z*sizeof(dev[0]), cudaMemcpyHostToDevice);
  multiply <<< X, blocks >>> (dev);
  cudaMemcpy(host, dev, X*Y*Z*sizeof(dev[0]), cudaMemcpyDeviceToHost);
  for (i = 0; i < X*Y*Z; i++)
    printf("%d\n", host[i]);
}

