#include<cstdio>
int s[5001];
main() {
  int i, j, k, n, sum;
  while (scanf("%d", &n) > 0 && n) {
    for (i = 0; i < n; ++i)
      scanf("%d", s+i);
    for (j = 0; j < n && s[j] == 0; ++j);
    for (k = 0; j+k < n && s[n-1-k] == 0; ++k);
    sum = (j + k + (j+k == n))/2;
    for (; j+k < n; ++j) {
      for (i = 0; s[i+j] == 0; ++i);
      sum += i/2;
      j += i;
    }
    printf("%d\n", sum);
  }
}
