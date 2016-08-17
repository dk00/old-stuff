#include<cstdio>
const int N = 50001;
int s[N], left[N];
main() {
  int a, i, j, k, n, T, C=1;
  long long sum;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    sum = 0;
    for (i = j = 0; i < n; i++) {
      scanf("%d", &a);
      sum += (i+1ll)*(n-i)*a;
      for (k = 0; j > 0 && a <= s[j-1];) {
        j--;
        sum -= s[j]*((left[j]+1ll)*(k+1)*(k+2)/2 + left[j]*(left[j]+1ll)/2*(k+1));
        k += left[j]+1;
      }
      left[j] = k;
      s[j++] = a;
    }
    for (k = 0; j > 0; ) {
      j--;
      sum -= s[j]*((left[j]+1ll)*(k+1)*(k+2)/2 + left[j]*(left[j]+1ll)/2*(k+1));
      k += left[j]+1;
    }
    printf("Case %d: %lld\n", C++, sum);
  }
}
