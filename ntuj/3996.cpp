#include<cstdio>
int num[99];
inline void count(int x) {
  while (x > 0) {
    ++num[x%10];
    x /= 10;
  }
}
main() {
  int T, n, i;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0; i < 10; ++i)
      num[i] = 0;
    for (i = 1; i <= n; ++i)
      count(i);
    printf("%d", num[0]);
    for (i = 1; i < 10; ++i)
      printf(" %d", num[i]);
    puts("");
  }
}
