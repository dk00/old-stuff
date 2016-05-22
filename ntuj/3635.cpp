#include<cmath>
#include<cstdio>
const double pi = 2*acos(-1.0);
const int N = 10001;
int n, m;
double s[N];
double test(double z) {
  int i;
  double sum;
  for (sum = i = 0; i < n; ++i)
    sum += floor(s[i]/z);
  return sum;
}
main() {
  int i, T;
  double z, a, lb, ub, sum;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    sum = 0;
    for (i = 0; i < n; ++i) {
      scanf("%lf", s+i);
      s[i] = s[i]*s[i]*pi/2;
      sum += s[i];
    }
    for (a = lb = s[0]/(m + 1), ub = sum/(m + 1); lb + 1e-5 < ub;) {
      z = (lb + ub)/2;    
      if (test(z) >= m + 1) a =  lb = z;
      else ub = z;
    }
    printf("%lf\n", a);
  }
}
