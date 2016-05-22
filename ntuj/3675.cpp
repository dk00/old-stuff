#include <stdio.h>

long long XC[35][35];

inline long long C(int a, int b){
  if(a<b) return 0ll;
  return XC[a-b][b];
}

long long f(int i, int x, long long n) {
  if(i<0) return 0;
  if(x==0) return (i==0);
  long long ret = 0;
  if((1<<(x-1)) & n) ret = C(x-1, i) + f(i-1, x-1, n);
  else ret = f(i, x-1, n);
  return ret;
}

long long getans(int i, int x, long long k) {
  if(x==0) return 0ll;
  if(C(x-1, i) < k) {
    return getans(i-1, x-1, k-C(x-1, i)) + (1ll<<(x-1));
  } else {
    return getans(i, x-1, k);
  }
}

int main(void)
{
  long long m, n, k;
  int T;
  scanf("%d", &T);
  for(int i = 0; i <= 31; i++)
    for(int j = 0; j <= 31; j++)
      if(i==0 || j==0) XC[i][j] = 1;
      else XC[i][j] = XC[i-1][j] + XC[i][j-1];
  while(T--){
    scanf("%lld%lld%lld", &m, &n, &k);
    long long ans = 0;
    if(m==0 && n==0){
      ans = 0;
    } if(m>0||n>0){
      for(int i=0;i<=31;i++){
        long long u = f(i, 31, n), v = ((m==0)? 0: f(i, 31, m-1));
        if (u - v < k) {
          k -= (u - v);
        } else {
          ans = getans(i, 31, k + v);
          break;
        }
      }
    } else if (n==0 && k==0){
      ans = 0;
    } else {
      k = (n-m+2)-k;
      for(int i=0;i<=31;i++){
        //TODO xiao_xing!!!
        long long u = f(i, 31, ~m), v = (n==-1? 0: f(i, 31, (~n)-1));
        //printf("i=%d, u=%lld, v=%lld\n", i, u, v);
        if (u - v < k) {
          k -= (u - v);  
        } else {
          ans = ~getans(i, 31, k + v);
          break;
        }
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
