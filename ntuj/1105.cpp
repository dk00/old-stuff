#include<cstdio>
int gcd(int a, int b) {
  while ((a%=b) && (b%=a));
  return a+b;
}
main() {
  int i, j, k, l, a;
  while (scanf("%d %d %d", &i, &j, &k) == 3 && i+j+k) {
    printf("%d\n", i + j + k - gcd(i, j) - gcd(j, k) - gcd(k, i) + gcd(i, gcd(j, k)));
  }
}
