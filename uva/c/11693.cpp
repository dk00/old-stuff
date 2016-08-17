#include<queue>
#include<cstdio>
using namespace std;
const int N = 100, inf = 2000000000;
void sp(int st, int d[]) {
  int i, j;
  for (i = 0; i < n; ++i) 
    d[i] = inf, u[i] = 1;
  queue<int> Q;
  Q.push(st);
  d[st] = 0;
  while (!Q.empty()) {
    i = Q.top();
    Q.pop();
    u[i] = 1;
    for (j = 0; j < n; ++j)
      if (c[i][j] < inf && d[i] + c[i][j] < d[j]) {
        d[j] = d[i] + c[i][j];
        if (u[j]) {
          u[j] = 0;
          Q.push(j);
        }
      }
  }
}
bool test(int a0, int b0, int a1, int b1) {
  return (a0*b1 > a1*b0);
}
double solve(int st) {
  int i, j;
  for (i = 0; i < n; ++i) {
    du[i] = 0;
    dl[i] = 1;
    u[i] = 1;
  }
  queue<int> Q;
  du[st] = 1;
  dl[st] = 0;
  Q.push(st);
  while (!Q.empty()) {
    i = Q.top();
    Q.pop();
    u[i] = 1;
    for (j = 0; j < n; ++j) {
      if (d[i] + c[i][j] >= d[j]) continue;
      if (test(dis_p[i], dis_b[i], du[i], dl[i]))
        a = du[i], b = dl[i];
      else 
        a = dis_p[i], b = dis_b[i];
      if (test(a, b, du[j], dl[j])) {
        du[j] = a, dl[j] = b;
        if (u[j]) Q.push[j], u[j] = 0;
      }
    }
  }
  for (i = 0; i < n; ++i) {
    if (test(dis_p[i], dis_b[i], du[i], dl[i]))
      du[i] = dis_p[i], dl[i] = dis_b[i];
    if (du[i]*ml < mu*dl[i])
      mu = du[i], ml = dl[i];
  }
  return 160.0*mu/ml;
}
/*
 * d_p / d_b > 160 / s_b
 *
 * s_b > 160 d_b / d_p
 * */
main() {
  int i, j, k, E;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d", &n, &m, &E);
    for (i = 0; i < n; ++i) {
      exit[i] = 0;
      for (j = 0; j < n; ++j)
        c[i][j] = inf;
    }
    while (m--) {
      scanf("%d %d %d", &i, &j, &k);
      --i, --j;
      c[i][j] = c[j][i] = k;
    }
    while (E--) {
      scanf("%d", i);
      exit[i-1] = 1;
    }
    scanf("%d %d", &i, &j);
    sp(i, dis_b);
    sp(j, dis_p);
    double t = solve(i);
    if (t < 0) puts("IMPOSSIBLE");
    else printf("%lf\n", t);
  }
}
