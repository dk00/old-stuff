#include <stdio.h>
#include <set>
using namespace std;

long long s[105];

int ans[1005], na = 0;

int main(void)
{
  int T, cs = 0;
  long long i, j, k;
  i=1,j=1;
  s[0] = 1;
  for(T=0;T<45;T++) {
    s[T+1] = i+j;
    k = i;
    i = j;
    j = i+k;
  }

  scanf("%d", &T);
  while(T--) {
    int n;
    na = 1;
    ans[0] = 1;
    long long MOD = 10;
    scanf("%d", &n);
    for(i=0;i<n;i++){
      long long x;
      scanf("%lld", &x);
      int r=0;
      for(j=45;j>=0;j--)
        if(s[j] <= x) {
          ++r;
          x -= s[j];
        }
      for(j=0;j<na;j++)
        ans[j] *= r;
      for(j=0;j<na;j++) {
        if(ans[j] >= MOD) {
          if(j==na-1) ans[na++] = 0;
          ans[j+1] += ans[j]/MOD;
          ans[j] %= MOD;
        }
      }
    }
    printf("Case %d: ", ++cs);
    for(j=na-1;j>=0;j--){
      printf("%d", ans[j]);
    }
    printf("\n");
  }
  return 0;
}
