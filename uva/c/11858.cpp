#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1000005;
int s[N], t[N];
long long go(int st, int ed) {  
  int i, j, k, m = (st + ed)/2;
  long long sum = 0;
  if (st >= ed) return 0;
  sum = go(st, m) + go(m+1, ed);
  for (i = st, j = m+1, k = st; k <= ed; ++k) {
    if (j <= ed && (i > m || s[j] < s[i]))
      t[k] = s[j++], sum += m - i + 1;
    else t[k] = s[i++];
  }
  for (k = st; k <= ed; ++k) s[k] = t[k];
  return sum;
}
main() {
  int i, n;
  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; ++i)
      scanf("%d", s+i);
    printf("%lld\n", go(0, n-1));
  }
}
