#include<cstdio>
#include<algorithm>
using namespace std;
int s[999];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, n;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", s+i);
    for (i = k = 0; i < n; ++i)
      for (j = 1; j < n; ++j)
        if (s[j] < s[j-1]) {
          ++k;
          swap(s[j], s[j-1]);
        }
    if (k % 2 != 0) puts("impossible");
    else {
    }
  }
}
