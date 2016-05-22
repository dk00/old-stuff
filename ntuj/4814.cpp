#include<cstdio>
#include<algorithm>
using namespace std;
int test(int a, int b, int c, int d, int e, int f) {
  int a0 = max(a, max(b, c)), a1 = min(max(a, b), min(max(b, c), max(a, c))),
      b1 = min(d, min(e, f)), b0 = max(min(d, e), max(min(e, f), min(d, f)));
  if (a0 > b0 && a1 > b1) return 0;
  return 1;
}
main() {
  int i, a, b, c, d, e;
  while (scanf("%d %d %d %d %d", &a, &b, &c, &d, &e) == 5 && a+b+c+d+e) {
    for (i = 1; i <= 52; ++i)
      if (a != i && b != i && c != i && d != i && e != i && test(a, b, c, d, e, i))
        break;
    if (i <= 52) printf("%d\n", i);
    else puts("-1");
  }
}
