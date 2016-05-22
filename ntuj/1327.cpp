#include<cstdio>
const int N = 50, W = 50, M = (N+1)*W*100;
int gcd(int a, int b) {
  while ((a%=b)&&(b%=a));
  return a + b;
}
int num[W], s[M];
main() {
  int i, j, k, l, r, n, t, lb, sum, lim, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &t, &n);
    for (j = 0; j <= W; ++j)
      num[j] = 0;
    lb = sum = 0;
    for (i = 0; i < n; ++i) {
      scanf("%d %d %d", &l, &r, &j);
      sum += j;
      lb += l*j;
      num[j] += r - l;
    }
    t *= sum;
    for (i = 0; i <= M; ++i)
      s[i] = -1;
    s[0] = 0;
    lim = 0;
    for (j = 1; j <= W; ++j) {
      if (num[j] < 1) continue;
      lim += j*num[j];
      for (i = 0; i <= lim; ++i)
        if (s[i] > 0) s[i] = 0;
      for (i = j; i <= lim; ++i) {
        k = s[i-j] + 1;
        if (k < 1 || k > num[j] || (s[i] >= 0 && k > s[i])) continue;
        s[i] = k;
      }
    }
    t -= lb;
    for (i = 0; i <= M; ++i)
      if ((t - i >= 0 && s[t-i] >= 0) || 
          (t + i >= 0 && t + i < M && s[t+i] >= 0))
        break;
    j = gcd(i, sum);
    i /= j;
    sum /= j;
    printf("%d/%d\n", i, sum);
  }
}
