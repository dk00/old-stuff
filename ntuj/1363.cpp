#include<cstdio>
long long M = 1ll << 50;
void Init() {
  k = 1 << n;
  for (i = 0; i < k; ++i)
    for (j = 0; j < k; ++j)
      c[i][j] = 0;

}
main() {
  while (scanf("%d %d", &n, &m) == 2) {
    Init();
  }
}
