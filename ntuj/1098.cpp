#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 160000;
int s[N];
main() {
  int i, j, k, n;
  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; ++i) {
      scanf("%d %d", &s[i*2], &s[i*2+1]);
      s[i*2] *= 2;
      s[i*2+1] *= 2;
      ++s[i*2+1];
    }
    sort(s, s+n*2);
    for (i = k = j = 0; i < n*2; ++i) {
      if (s[i]&1) --j;
      else ++j;
      if (j > k) k = j;
    }
    printf("%d\n", k);
  }
}
