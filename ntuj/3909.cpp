#include<cstdio>
const int N = 100008;
int s1[N], s2[N];
main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n0, &n1);
    memset(s0, 0, sizeof(s0));
    memset(s1, 0, sizeof(s1));
    for (i = 0; i < n0; ++i) {
      scanf("%d", &j);
      ++s0[j];
    }
    for (i = 0; i < n1; ++i) {
      scanf("%d", &j);
      ++s1[j];
    }
    
  }
}
