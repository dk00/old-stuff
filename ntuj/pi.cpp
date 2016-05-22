#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

class Point{
  public:
    long long x, y;
    Point(long long xx=0, long long yy=0) {
      x=xx; y=yy;
    }
    bool operator <(const Point &u) const {
      return x < u.x || x==u.x && y<u.y;
    }
    Point operator +(const Point &u) const {
      return Point(x+u.x, y+u.y);
    }
    Point operator -(const Point &u) const {
      return Point(x-u.x, y-u.y);
    }
    long long cross(const Point &u) const{
      return x*u.y - y*u.x;
    }
    long long dist(const Point &u) const{
      return (x-u.x)*(x-u.x)+(y-u.y)*(y-u.y);
    }
} p[100005], q[100005], dp[100005], dq[100005];
Point stack[100005];
int top=0, dpi, dqi;

bool cmp(const Point &x, const Point &y) {
  return x.cross(y) > 0;
}

void convex_hull(Point *r, int n, Point *dr, int &dri) {
  int i, mi=0;
  
  Point mn = r[0],backup;
  for(i=0;i<n;i++)
    if(r[i] < mn) {
      //printf("i=%d\n", i);
      mn = r[i];
      mi = i;
    }
  backup = r[mi];
  r[mi] = r[0];
  r[0] = backup;

  backup = r[0];
  /*for(i=0;i<n;i++)
    printf("%lld, %lld\n", r[i].x, r[i].y);
  printf("======\n");  */
  
  for(i=0;i<n;i++)
    r[i] = r[i] - backup;
  sort(r+1, r+n, cmp);

  
  r[n] = r[0];
  top=0;
  stack[top++] = r[0];
  for(i=1;i<=n;i++) {
    while(top>2 && (stack[top-1]-stack[top-2]).cross(r[i]-stack[top-1])<=0)
      --top;
    stack[top++] = r[i];
  }
  for(i=0;i<top;i++)
    dr[i] = stack[i] + backup;
  dri = top;
  /*for(i=0;i<dri;i++)
    printf("%lld %lld\n", dr[i].x, dr[i].y);
  printf("====\n");*/
}

int main(void) {
  int T, i, j;
  scanf("%d", &T);
  while(T--){
    int np, nq;
    scanf("%d", &np);
    for(i=0;i<np;i++){
      scanf("%lld%lld", &p[i].x, &p[i].y);
    }
    scanf("%d", &nq);
    for(i=0;i<nq;i++){
      scanf("%lld%lld", &q[i].x, &q[i].y);
    }
    convex_hull(p, np, dp, dpi);
    convex_hull(q, nq, dq, dqi);
    long long dist=0;
    for(i=0;i<dpi;i++)
      for(j=0;j<dqi;j++)
        if(dist < dp[i].dist(dq[j]))
          dist = dp[i].dist(dq[j]);
    printf("%.3lf\n", sqrt(dist));
  }
  return 0;
}
