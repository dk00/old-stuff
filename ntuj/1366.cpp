#include<cstdio>
#include<algorithm>
using namespace std;
main() {
  int i, j, k, o, n, T;
  char tmp[111];
  scanf("%d", &T);
  while (T--) {
    scanf("%s", tmp);
    for (n = 0; tmp[n]; ++n);
    for (i = k = o = 0; i < n; ++i) {
      if (!tmp[i]) continue;
      k += o;
      for (j = n - 1; j > i && tmp[j] != tmp[i]; --j);
      if (j <= i) {
        if (o > 0) break;
        ++o;
        tmp[i] = 0;
        continue;
      }
      tmp[i] = tmp[j] = 0;
      for (;j < n; ++j)
        if (tmp[j]) ++k;
    }
    if (i < n) puts("Impossible");
    else printf("%d\n", k);
  }
}
