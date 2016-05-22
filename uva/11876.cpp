#include<cstdio>
const int N = 1000001;
int s[N];
main() {
  int i, j, k, T, C = 1;
  for (i = 1; i < N; i += j) {
    s[i] = 1;
    for (j = 0, k = 1; i/k > k; ++k)
      if (i%k == 0) j += 2;
    if (k*k == i) ++j;
  }
  for (i = 1; i < N; ++i)
    s[i] += s[i-1];
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &i, &j);
    printf("Case %d: %d\n", C++, s[j] - s[i-1]);
  }
}
