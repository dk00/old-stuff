#include<map>
#include<queue>
#include<cstdio>
using namespace std;
const int N = 10000, M = 2012;
bool notp[N];
int p[M], u[M], d[M];
int main() {  
  int i, j, k, l, tmp, n = 0, un = 0, m, T;
  map<int, int> H;
  for (i = 3; i < N; i += 2) {
    if (notp[i]) continue;
    for (j = i*3; j < N; j += i*2) notp[j] = true;
    if (i > 1000) {
      H[i] = n;
      p[n++] = i;
    }
  }
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &i, &m);
    if (!H.count(m)) {
      puts("Impossible");
      continue;
    }
    m = H[m];
    queue<int> Q;
    Q.push(i);
    ++un;
    if (H.count(i)) {
      d[H[i]] = 0;
      u[H[i]] = un;
    }
    while (!Q.empty()) {
      i = Q.front();
      Q.pop();
      if (H.count(i)) tmp = d[H[i]];
      else tmp = 0;
      for (j = 0; j < 10; j++)
        for (k = 1; k <= 1000; k *= 10) {
          l = i - i%(k*10)/k*k + j*k;
          if (!H.count(l) || u[H[l]] == un) continue;          
          Q.push(l);
          u[l=H[l]] = un;
          d[l] = 1 + tmp;
        }
    }
    if (u[m] == un) printf("%d\n", d[m]);
    else puts("Impossible");
  }
}
