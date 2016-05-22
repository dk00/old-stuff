#include <stdio.h>
#include <string.h>
#include <math.h>

const double eps = 1e-5;

inline double getavg(double c, long long L, long long R) {
  double err = (c / L - c / R);
  if(err > eps && R > L) {
    long long M = (L+R)/2;
    return (getavg(c, L, M) * (M+1-L) / (R+1-L)
        + getavg(c, (L+R)/2+1, R) * (R-M) / (R+1-L));
  }
  return c / L;
}

int main(void)
{
  int cs=0;
  long long W, L;
  while(scanf("%lld%lld\n", &W, &L)!=EOF) {
    if(W==0 && L==0) break;
    long long N1, N2;
    if(L*7 >= W) {
      N1 = L;
    } else {
      N1 = L + (W - 7*L + 7) / 8;
    }
    N2 = L + W/8;
    //double n = N1, ans = 0.0, LIMIT = 100000;
    /*
    while(n <= N2 && LIMIT>=0) {
      LIMIT -= 1.0;
      ans += (W+L)/n / (N2-N1+1);
      n += 1.0;
    }*/
    double ans;
    ans = getavg((double)W+L, N1, N2);
    printf("Case %d:\n", ++cs);
    if(L==0) {
      if(W % 8 != 0) {
        printf("Situation Impossible.\n");
      } else {
        printf("On Average Bob Reaches Round 8.00\n");
      }
    } else {
      printf("On Average Bob Reaches Round %.2lf\n", ans);
    }
  }
  return 0;
}
