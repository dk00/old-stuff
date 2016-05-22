#include<stdio.h>

#ifndef N
#define N 3000000
#endif
char composite[N];

int main() {
  int i, j, k, count;
  count = 1;
  for (i = 3; i <= N/i; i += 2) {
    if (composite[i]) continue;
    count++;
    for (j = i; i*j < N; j += 2)
      composite[i*j] = 1;
  }
  for (; i < N; i += 2)
    count += !composite[i];

  printf("%d\n", count);
  return 0;
}
