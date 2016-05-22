#include<cstdio>
const int M = 24*60;
int s[M];
void add(char a[], char b[]) {
  int i, j, x, y;
  sscanf(a, "%d:%d", &x, &y);
  i = x * 60 + y;
  sscanf(b, "%d:%d", &x, &y);
  j = x * 60 + y;
  if (i > j) x = i, i = j, j = x;
  for (; i <= j; ++i)
    ++s[i];
}
void print(int a, int b) {
  printf("%02d:%02d %02d:%02d\n", a/60, a % 60, b/60, b%60);
}
char a[99], b[99];
main() {
  int i, j, k, n, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0; i < M; ++i)
      s[i] = 0;
    for (i = 0; i < n; ++i) {
      scanf("%s %s", a, b);
      add(a, b);
    }
    for (i = j = k = 0; i < M; ++i)
      if (s[i] > j) j = s[i], k = i;
    for (i = k; s[i] == s[k] && i < M; ++i);
    print(k, i-1);
  }
}
