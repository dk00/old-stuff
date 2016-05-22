#include<cstdio>
void init (int& a, int& b, int& c, int k) {
  a = k%3;
  if (k%2) b = (a+1) % 3;
  c = 6 - a - b;
}
main() {
  scanf("%d", &T);
  scanf("%d %d", &n, &k);
  init (a, b, c, k);
  for (i = 4; i <= n; ++i) {
    a = (a + k%i)%m;
    b = (b + k%i)%m;
    c = (c + k%i)%m;    
  }
  printf("%d %d %d\n", a, b, c);
}
