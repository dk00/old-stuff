#include<cstdio>
#include<algorithm>
using namespace std;
long long lcm(int a, int b) {
  long long c = 1ll * a * b;
  while((a%=b)&&(a%=b));
  return 1ll * c / (a + b);
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d %d %d", &n, &c0, &g0, &c1, &g1);
    if (c0 - g0 < c1 - g1)
      swap(c0, c1), swap(g0, g1);
    if (c0 <= g0) {
      puts("DRAGON");
      continue;
    }
    if (c1 == g1) {
      if (n >= c0 && n%(c0 - g0) == c0 % (c0 - g0))
        puts("PRINCE");
      else if (n + 1 >= c0 && (n + 1)%(c0 - g0) == c0%(c0 - g0))
        puts("DRAW");
      else puts("DRAGON");
      continue;
    }
    if (c1 < g1) {
    }
    else {
      if (c0 > c1)
        swap(c0, c1), swap(g0, g1);      
      base = lcm(c0 - g0, c1 - g1) / (c0 - g0);
      base *= n /((c0 - g0)* base);
      for (i = base; (c0 - g0)* i < n; ++i)

    }
  }
}
