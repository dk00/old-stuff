#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 131072;

void build() {
  for (i = 0; i < n; ++i)
    s[p[i]] += s[i];
}

main() {
  for (i = 0; i < N - 1; ++i) {
    for (j = 0; (1<<j)&i; ++j);
    p[i] = i|(1<<j);
  }
  while (scanf("%d %d", &n, &m) == 2) {
    for (i = 0; i < n; ++i)
      scanf("%d", s+i);
    sort(s, s+n);
    for (i = n - 1; i > 0; --i)
      s[i] -= s[i-1];
    for (i = 0; (1<<i) <= n; ++i)
      n |= 1<<i;
    for (i = 0; i <= n; ++i)
      s[p[i]] += s[i];
    while (m--) {
      scanf("%s", tmp);
      if (tmp[0] == 'F') {
        scanf("%d %d", &i, &j);
        add(find(i), j);
      }
    }
  }
}
