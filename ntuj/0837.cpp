#include<cstdio>
#include<algorithm>
using namespace std;
int s0[99], s1[99];
main() {
  int i, j, n, m;
  while (scanf("%d %d", &n, &m) == 2 && n+m) {
    for (i = 0; i < n; ++i)
      scanf("%d", s0+i);
    for (j = 0; j < m; ++j)
      scanf("%d", s1+j);
    sort(s0, s0+n);
    sort(s1, s1+m);
    for (i = 0; i < n; ++i)
      if (s0[i] < s1[1]) break;
    if (i < n) puts("Y");
    else puts("N");
  }
}
