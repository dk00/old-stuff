#include<cstdio>
#include<cstring>
const int N = 100005;
const long long inf = N*1ll*N;
inline int abs(int a) {return a<0?-a:a;}
long long gcd(long long a, long long b) {
  while ((a%=b)&&(b%=a));
  return a+b;
}
int n, m, x[N], y[N], p[2][N];
long long s[2][N];
inline int Cost(int s[], int a, int b) {
  return abs((s[b] - (a?s[a-1]:0)) - n);
}
long long Solve(int x[], int n) {
  int i, j, k;
  for (i = 1; i < n; ++i)
    x[i] += x[i-1];
  for (i = 0; i < n; ++i) {
    s[0][i] = s[1][i] = inf;
    p[0][i] = p[1][i] = 0;
    x[i] *= m;
  }
  const int M0 = 3;
  for (j = 0; j < m; ++j) {
    for (i = k = 0; i < n; ++i) {
      s[j%2][i] = j * Cost(x, 1, 0) + Cost(x, 0, i);
      if (k < M0) k = 0;
      else k -= M0;
      for (; k < i; ++k) {
        long long tmp = s[1-j%2][k] + Cost(x, k+1, i);
        if (tmp > s[j%2][i]) { 
          if (k > 0) k--;
          break;
        }
        p[j%2][i] = k;        
        s[j%2][i] = tmp;
      }
      long long tmp = s[1-j%2][k] + Cost(x, 1, 0);
      if (tmp < s[j%2][i])
        s[j%2][i] = tmp;
    }
  }
  return s[1-j%2][n-1];
}

int main() {
  int i, j, max_x, max_y, C = 1;
  long long k, l;
  while (scanf("%d %d", &n, &m) == 2 && n+m) {
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    max_x = max_y = 0;
    for (i = 0; i < n; ++i) {
      scanf("%d %lld", &j, &k);
      if (j > max_x) max_x = j;
      if (k > max_y) max_y = k;
      ++x[j], ++y[k];
    }
    k = Solve(x, max_x + 1);
    l = Solve(y, max_y + 1);
    if (l < k) k = l;
    if (k == 0)
      printf("%d. 0/1\n", C++);
    else {
      j = gcd(k, m*m);
      printf("%d. %lld/%d\n", C++, k/j, m*m/j);
    }

  }
}
