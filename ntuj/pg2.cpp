#include <stdio.h>
#include <math.h>

double c[20005], s[20005];
int main(void)
{
   double PI2 = acos(-1.0)/2.0, eps = 0.001, EPS=5e-3;
  double a[20005][3];
  double t;


  int n;
  int T, i;
  scanf("%d", &T);
    for(i=0,t=0;t<PI2;t+=eps, ++i) {
      c[i] = cos(t);
      s[i] = sin(t);
    }
  while(T--){
    double v;
    scanf("%lf", &v);
    scanf("%d", &n);
    for(i=0;i<n;i++)
      scanf("%lf%lf%lf", &a[i][0], &a[i][1], &a[i][2]);
   
    int ans=0;
    for(t=0,i=0;t<PI2;t+=eps,++i) {
      double vx = v * c[i];
      double vy = v * s[i];
      int cnt=0;
      for(i=0;i<n;i++) {
        double tt = a[i][0] / vx;
        double h = vy*tt - 5.0*tt*tt;
        if(h >= a[i][1] - EPS && h <= a[i][2] + EPS)
          ++cnt;
      }
      if(cnt > ans)
        ans = cnt;
    }
    printf("%d\n", ans);
  }
  return 0;
}
