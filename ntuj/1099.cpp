#include <stdio.h>

long long mergesort(int a[], int tmp[], int n)
{
  long long ret = 0;
  if(n <= 1) return 0;
  int m = (n+1) / 2;
  ret += mergesort(a, tmp, m);
  ret += mergesort(a+m, tmp+m, n-m);
  int i = 0, j = m, k = 0;
  while(i < m || j < n) {
    if (j == n || i < m && a[i] < a[j]) {
      tmp[k++] = a[i++];
      ret += j - m;
    } else {
      tmp[k++] = a[j++];
    }
  }
  for(i = 0; i < n; i++)
    a[i] = tmp[i];
  return ret;
}

int a[100005], b[100005], t[100005], p[100005];

int main(void)
{
  int n, i;
  while(scanf("%d", &n) != EOF) {
    for(i=0;i<n;i++) {
      scanf("%d", &a[i]);
      b[i] = a[i];
      p[a[i]-1] = i;
    }
    long long sum = mergesort(b, t, n), ans = sum;
    for(i=n-1;i>=0;i--){
      sum = sum + p[i] - (n - p[i] - 1);
      if (ans > sum) ans = sum;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
