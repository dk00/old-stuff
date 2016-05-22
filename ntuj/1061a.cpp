#include<stack>
#include<cstdio>
int s[999999];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, n;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", s+i);
    for (j = n/2; j > 0; --j) {
      for (i = 0; i <= j/2; ++i)
        if (s[i] > s[j+i] || s[j-i-1] > s[2*j-i-1]) break;
      if (i > j/2) break;
    }
    printf("%d\n", j);
  }
}
