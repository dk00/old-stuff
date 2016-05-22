#include<cstdio>
inline int Sum(int n) {
  return n*(n+1)*(2*n+1)/6;
}
main() {
  int T, n, k;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &k);
    printf("%d\n", Sum(2*n) - Sum(2*k) 
        - 4*(n - k)*(2*k + 1)*(2*k + 1)
        + 4*k*(2*k + 1)*(2*k + 1));
  }
}
/*
 1, 5, 14, 30
 30 - 5 -
 
 */
