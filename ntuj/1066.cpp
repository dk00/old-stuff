#include<cstdio>
void init (int& a, int& b, int& c, int k) {
  a = k%3;
  if (a == 0) a = 3;
  if (k%2) b = (a+1) % 3;
  else b = (a+2) %3;
  if (b == 0) b = 3;
  c = 6 - a - b;
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, a, b, c, n, k;
    scanf("%d %d", &n, &k);
    init (a, b, c, k);
    for (i = 4; i <= n; ++i) {
      a = (a + k)%i;
      b = (b + k)%i;
      c = (c + k)%i;
      if (a == 0) a = i;
      if (b == 0) b = i;
      if (c == 0) c = i;      
    }
    printf("%d %d %d\n", a, b, c);
  }
}
