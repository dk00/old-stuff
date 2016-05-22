#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

double a[205][2];
int n, k;
double dist(double xa, double ya, double xb,
    double yb, double xc, double yc)
{
  return (xc-xa)*(yb-ya)-(yc-ya)*(xb-xa);
}
double len(int i, int j){
  return sqrt(
      (a[j][0]-a[i][0])*(a[j][0]-a[i][0])+(a[j][1]-a[i][1])*(a[j][1]-a[i][1])
      );
}

const double eps = 1e-10, inf=1e30;
double go(int x, int y)
{
  int i;
  int cnt = 2;
  vector<double> p, q;
  for(i=0;i<n;i++){
    if(i!=x && i!=y){
      double d = dist(a[x][0], a[x][1], a[y][0], a[y][1], a[i][0], a[i][1]);
      if(d > -eps && d < eps)
        ++cnt;
      else if(d < 0){
        p.push_back(-d);
      }else if(d > 0){
        q.push_back(d);
      }
    }
  }
  if(k<=cnt)
  return 0.0;
  sort(p.begin(), p.end());
  sort(q.begin(), q.end());
  double x1 = (p.size() >= k-cnt)? p[k-cnt-1]:inf;
  double x2 = (q.size() >= k-cnt)? q[k-cnt-1]:inf;
  if(x1>=inf && x2>=inf)
    return inf;
  return (x1<x2?x1:x2) / len(x, y);
}

int main(void)
{
  int i, j;
  scanf("%d%d", &n, &k);
  for(i=0;i<n;i++)
     scanf("%lf%lf", &a[i][0], &a[i][1]);
  if(k<=2){
    printf("0.000000\n");
  }else{
    double ans = -10000;
    for(i=0;i<n;i++)
      for(j=i+1;j<n;j++)
      {
        double t = go(i, j);
  //      printf("i=%d, j=%d, t=%lf\n", i, j, t);
        if(ans < 0 || t < ans)
          ans = t;
      }
    if (ans < 1 + eps) {
      printf("0.000000\n");
    }
    else {
      ans -= 1;
      printf("%.10lf\n", ans);
    }
  }
  return 0;
}
