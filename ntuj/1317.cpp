#include<cstdio>
int m;
int pow(int n, int k) {
  if (k == 0) return 1;
  if (k%2) return n*1ll*pow(n, k-1)%m;
  n = pow(n, k/2);
  return n*1ll*n%m;
}
main() {
  int T, a, b, x, sum;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d %d", &a, &b, &x, &m);
    for (sum = 0;a <= b; ++a) {
      sum += pow(a, x);
      sum %= m;
    }
    printf("%d\n", sum);
  }
}
