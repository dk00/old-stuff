#include <stdio.h>
#include <algorithm>
using namespace std;

const long long MOD = 1000000007;
long long INV2, INV3;

long long inv(long long x, long long y, long long p, long long q, long long r, long long s) {
  if(y==0) return p%MOD;
  return inv(y, x%y, r, s, p-x/y*r, q-x/y*s);
}
long long even_all(long long n) {
  long long x = n/2-1;
  long long r = x*(x+1)%MOD*INV2%MOD*(2*x+1)%MOD*INV3%MOD;
  //printf("even %lld\n", r+MOD);
  return r;
//  return x*(x+1)%MOD*INV2%MOD*(x-1)%MOD*INV3%MOD;
}
long long odd_all(long long n) {
  long long x = (n+1)/2-2;
  return x*(x+1)%MOD*(x+2)%MOD*INV3%MOD;
//  return x*(x-1)%MOD*INV2%MOD*(x+4)%MOD*INV3%MOD;
}
long long single(long long k, long long n) {
  long long small, rk;
  rk = k;
  if(rk > n-k+1)
    rk = n-k+1;
  small = (k-1)*(n-2*k+1>=0? n-2*k+1:0) + (rk-1)*(rk-2)%MOD*INV2;
  small = (small%MOD + MOD)%MOD;
  long long med;
  med = (rk-2)*(rk-1)%MOD * INV2 % MOD;
  //printf("med=%lld\n", med+MOD);
  if(rk < k) {
    med = (med + (k-rk)*(n-k)) % MOD;
  }
  med = (med%MOD+MOD)%MOD;
  long long large;
  long long x = k/2;
  large = x*(x-1)%MOD;
  if(k%2==0)
    large -= (x-1);
  large = (large%MOD + MOD) % MOD;
  //printf("small=%lld, med=%lld, large=%lld\n", small, med, large);
  return (small + med + large) % MOD;

}

long long two(long long x, long long y, long long n) {
  long long L = y-x+1, R = x+y-1, r;
  if(R>n) R = n;
  if(L<=0) L = 1;
  r=R-L+1;
  if(x>=L && x<=R) --r;
  if(y>=L && y<=R) --r;
  
  //printf("x=%lld, y=%lld, L=%lld, R=%lld r=%lld\n", x, y, L, R, r);
  return r;
}
long long a[1005];
int main(void)
{
  long long n, m;
  int i, j, k;
  INV2 = inv(2, MOD, 1, 0, 0, 1);
  INV3 = inv(3, MOD, 1, 0, 0, 1);
  while(scanf("%lld%lld", &n, &m)!=EOF) {
    long long ans = 0;
    ans += even_all(n);
    ans += odd_all(n);
    //printf("ans=%lld\n", ((ans%MOD)+MOD)%MOD);
    for(i=0;i<m;i++) {
      scanf("%lld", &a[i]);
      for(j=0;j<i;j++)
        if(a[i]==a[j])
          break;
      if(j<i || a[i]<=0 || a[i]>n) --m;
    }
    for(i=0;i<m;i++) {
      ans = (ans - single(a[i], n)) %MOD;
    }
    sort(a, a+m);
    for(i=0;i<m;i++) {
      for(j=i+1;j<m;j++) {
        ans = (ans + two(a[i], a[j], n)) % MOD;
      }
    }
    //TODO: three
    
    for(i=0;i<m;i++) {
      for(j=i+1,k=j+1;j<m;j++) {
        while(k<m && a[i]+a[j]>a[k]) ++k;
        ans -= k-j-1;
      }
/*
      for(j=i+1;j<m;j++)
        for(k=j+1;k<m;k++)
          if(a[i]+a[j]>a[k]) --ans;*/
    }
    ans = (ans%MOD + MOD) % MOD;
    printf("%lld\n", ans);
  }
  return 0;
}
