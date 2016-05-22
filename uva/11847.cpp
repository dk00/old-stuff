#include<cstdio>
main() {
  int i, n;
  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; n > 1; n /= 2, ++i);
    printf("%d\n", i);
  }
}
