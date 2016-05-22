#include <stdio.h>
#include <math.h>
#include <algorithm>
//#include <iostream>
using namespace std;
double p[10005][3];
double e[20005][2];
int ne=0;
double const PI = acos(-1.0);

void solve(double x, double y, double v0, double &t1, double &t2, int &flag) {
  double P, Q, R, theta1, theta2;
  P = v0*v0 - 25.0;
  Q = 50.0*y / x;
  R = -(25.0*y*y/x*x+25.0);
  double D;
  double A, B;
  D = Q*Q-4*P*R;
  if(P<1e-10 && P>-1e-10) {t1=t2=-1;flag=0; return;}
  if(D<0) {
    //NO solution
    flag = 0;
    t1=t2=-1;
  } else {
    A = (-Q-sqrt(Q*Q-4*P*R)) / P;
    B = -A*x + y/x;
    theta1 = atan(B);
    A = (-Q+sqrt(Q*Q-4*P*R)) / P;
    B = -A*x + y/x;
    theta2 = atan(B);
    t1 = theta1;
    t2 = theta2;
    if(t1<0) {t1 = t2; t2 = -1;}
    flag = 1;
    //cout << A << " " << B << "; P=" << P << " Q=" << Q << " R=" << R <<endl;
  }
}

int no[100005], nv=0;
double v[100005];
int type[100005];
int srt[100005];

double EPS = 1e-6;

void getpos(double *a, double v0, int i) {
  double t1, t2, t3, t4;
  int f1, f2;
  
  solve(a[0], a[1], v0, t1, t2, f1);
  solve(a[0], a[2], v0, t3, t4, f2);
 //printf("[%d] %lf %lf [%d] %lf %lf\n", f1, t1/PI*180.0,
 //     t2/PI*180.0, f2, t3/PI*180.0, t4/PI*180.0);
  if(t2>0 && t1>0 && t3>0 && t4>0) {
    no[nv] = i;
    v[nv] = t1;
    type[nv++] = 1;
    no[nv] = i;
    v[nv] = t3;
    type[nv++] = -1;
    no[nv] = i;
    v[nv] = t2;
    type[nv++] = 1;
    no[nv] = i;
    v[nv] = t4;
    type[nv++] = -1;
  } else if(t1 > 0 && t3 > 0) {
    no[nv] = i;
    v[nv] = t1;
    type[nv++] = 1;
    no[nv] = i;
    v[nv] = t3;
    type[nv++] = -1;
  }
}
bool same(double &x, double &y) {
  return x<y+EPS && y<x+EPS;
}
bool cmp(int x, int y) {
  return v[x] < v[y] || same(v[x], v[y]) && type[x] > type[y];
}
int main(void)
{
  int T, i, j;
  scanf("%d", &T);
  while(T--){
    double v0;
    int n;
    scanf("%lf", &v0);
    scanf("%d", &n);
    for(i=0;i<n;i++) {
      scanf("%lf%lf%lf", &p[i][0], &p[i][1], &p[i][2]);
    }
    ne=0;
    nv=0;
    for(i=0;i<n;i++) {
      getpos(p[i], v0, i);
    }
    for(i=0;i<nv;i++)
      srt[i] = i;
    sort(srt, srt+nv, cmp);
    int cnt=0, ans=0;#include <stdio.h>
#include <math.h>
#include <algorithm>
//#include <iostream>
using namespace std;
double p[10005][3];
double e[20005][2];
int ne=0;
double const PI = acos(-1.0);

void solve(double x, double y, double v0, double &t1, double &t2, int &flag) {
  double P, Q, R, theta1, theta2;
  P = v0*v0 - 25.0;
  Q = 50.0*y / x;
  R = -(25.0*y*y/x*x+25.0);
  double D;
  double A, B;
  D = Q*Q-4*P*R;
  if(P<1e-10 && P>-1e-10) {t1=t2=-1;flag=0; return;}
  if(D<0) {
    //NO solution
    flag = 0;
    t1=t2=-1;
  } else {
    A = (-Q-sqrt(Q*Q-4*P*R)) / P;
    B = -A*x + y/x;
    theta1 = atan(B);
    A = (-Q+sqrt(Q*Q-4*P*R)) / P;
    B = -A*x + y/x;
    theta2 = atan(B);
    t1 = theta1;
    t2 = theta2;
    if(t1<0) {t1 = t2; t2 = -1;}
    flag = 1;
    //cout << A << " " << B << "; P=" << P << " Q=" << Q << " R=" << R <<endl;
  }
}

int no[100005], nv=0;
double v[100005];
int type[100005];
int srt[100005];

double EPS = 1e-6;

void getpos(double *a, double v0, int i) {
  double t1, t2, t3, t4;
  int f1, f2;
  
  solve(a[0], a[1], v0, t1, t2, f1);
  solve(a[0], a[2], v0, t3, t4, f2);
 //printf("[%d] %lf %lf [%d] %lf %lf\n", f1, t1/PI*180.0,
 //     t2/PI*180.0, f2, t3/PI*180.0, t4/PI*180.0);
  if(t2>0 && t1>0 && t3>0 && t4>0) {
    no[nv] = i;
    v[nv] = t1;
    type[nv++] = 1;
    no[nv] = i;
    v[nv] = t3;
    type[nv++] = -1;
    no[nv] = i;
    v[nv] = t2;
    type[nv++] = 1;
    no[nv] = i;
    v[nv] = t4;
    type[nv++] = -1;
  } else if(t1 > 0 && t3 > 0) {
    no[nv] = i;
    v[nv] = t1;
    type[nv++] = 1;
    no[nv] = i;
    v[nv] = t3;
    type[nv++] = -1;
  }
}
bool same(double &x, double &y) {
  return x<y+EPS && y<x+EPS;
}
bool cmp(int x, int y) {
  return v[x] < v[y] || same(v[x], v[y]) && type[x] > type[y];
}
int main(void)
{
  int T, i, j;
  scanf("%d", &T);
  while(T--){
    double v0;
    int n;
    scanf("%lf", &v0);
    scanf("%d", &n);
    for(i=0;i<n;i++) {
      scanf("%lf%lf%lf", &p[i][0], &p[i][1], &p[i][2]);
    }
    ne=0;
    nv=0;
    for(i=0;i<n;i++) {
      getpos(p[i], v0, i);
    }
    for(i=0;i<nv;i++)
      srt[i] = i;
    sort(srt, srt+nv, cmp);
    int cnt=0, ans=0;
    int u[20005]={};
    for(j=0;j<nv;j++){
      i = srt[j];
      u[no[i]] += type[i];
      if(type[i]>0 && u[no[i]]==1)
        ++cnt;
      else if(type[i]<0 && u[no[i]]==0)
        --cnt;
      if(cnt > ans)
        ans = cnt;
    }
    printf("%d\n", ans);
  }
  return 0;
}
    int u[20005]={};
    for(j=0;j<nv;j++){
      i = srt[j];
      u[no[i]] += type[i];
      if(type[i]>0 && u[no[i]]==1)
        ++cnt;
      else if(type[i]<0 && u[no[i]]==0)
        --cnt;
      if(cnt > ans)
        ans = cnt;
    }
    printf("%d\n", ans);
  }
  return 0;
}
