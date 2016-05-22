#include<cstdio>
long long gcd(long long a, long long b) {
  while ((a%=b)&&(b%=a));
  return a+b;
} 
main() {
  long long a, b, c;
  while (scanf("%lld %lld", &a, &b)==2 && a+b) {
    c = gcd(a, b);
    printf("%lld\n", a/c*(b/c));
  }
}
