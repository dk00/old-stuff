#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int M = 1000001;
const long long P0 = 1000000007, P1 = 997;
int n;
long long p[M];
char g[6][M];
inline int H(int v, int c, int pre, int len) {
  return (((v - pre*p[len-1])*P1 + c)%P0 + P0)%P0;
}
int H0[2][M], nH[2];
inline bool appear(int v, int *arr, int n) {
  return (*lower_bound(arr, arr+n, v)) == v;
}
bool test(int len) {
  int i, k;
  int v;
  //set<int> H0[2];
  nH[0] = nH[1] = 0;
  for (k = 0; k < n; ++k) {
    //if (k > 0 && H0[k%2].size() == 0) return false;
    if (k > 0 && nH[k%2] == 0) return false;
    sort(H0[k%2], H0[k%2] + nH[k%2]);
    //H0[1-k%2].clear();
    nH[1-k%2] = 0;
    for (i = v = 0; g[k][i] && i < len; ++i)
      v = H(v, g[k][i], 0,  len);
    if (i < len) return false;
    for (; g[k][i]; ++i) {
      v = H(v, g[k][i], g[k][i-len],  len);    
      //if (k == 0 || H0[k%2].count(v))
      if (k == 0 || appear(v, H0[k%2], nH[k%2]))
        //H0[1-k%2].insert(v);
        H0[1-k%2][nH[1-k%2]++] = v;
    }
  }
  //return H0[k%2].size() > 0;
  return nH[k%2] > 0;
}
main() {
  int i, j, k, a, T;
  p[0] = 1;
  for (i = 1; i < M; ++i) 
    p[i] = p[i-1] * P1 % P0;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int sh = M;
    for (i = 0; i < n; ++i) {
      scanf("%s", g[i]);
      if (strlen(g[i]) < sh)
        sh = strlen(g[i]);
    }
    for (i = 1, j = sh; i <= j; ) {
      k = (i + j)/2;
      if (test(k)) a = k, i = k + 1;
      else j = k - 1;
    }
    printf("%d\n", a);
  }
}
