#include<stack>
#include<cstdio>
#include<cstring>
using namespace std;
struct pt {
  int st, ed;
};
const int N = 1111111, M = 65536;
int s[N], lt[N], gt[N], next[N], u[2*N], p[2*N], e[N];
char buf[M];
inline int getInt() {
  static char *end = buf + M, *p = end;
  if (p+20 >= end) {
    register int i;
    for (i = 0; p+i < end; ++i)
      buf[i] = *(p+i);
    fread(buf+i, sizeof(buf[0]), M-i, stdin);
    p = buf;
  }
  register int j = 0;
  register char *i;
  for (i = p; *i != '\n'; ++i)
    ((j *= 10) += *i) -= '0';
  while (*i == '\n') ++i;
  p = i;
  return j;
}
main() {
  int T = 1;
  T = getInt();
  while (T--) {
    register int i, j, k, n;
    n = getInt();
    stack<int> Hi, Hd;
    for (i = 0; i < n; ++i) {
      s[i] = getInt();
      while (!Hi.empty() && s[i] < s[Hi.top()]) {
        lt[Hi.top()] = i;
        Hi.pop();
      }
      Hi.push(i);
      while (!Hd.empty() && s[i] > s[Hd.top()])
        Hd.pop();
      if (Hd.empty()) gt[i] = -1;
      else gt[i] = Hd.top();
      Hd.push(i);
      j = n + s[i] - i;
      next[i] = n + 1;
      if (u[j] == T+1) next[p[j]] = i;
      u[j] = T+1;
      p[j] = i;
    }
    while (!Hd.empty()) {
      gt[Hd.top()] = -1;
      Hd.pop();
    }
    while (!Hi.empty()) {
      lt[Hi.top()] = n+1;
      Hi.pop();
    }
    for (i = 0; i < n; ++i) {
      j = n + s[i] - i;
      if (u[j] < 0) continue;
      u[j] = -1;
      stack<pt> S;
      for (k = i; k < n; k = next[k]) {
        e[k] = -1;
        while (!S.empty() && k > S.top().ed) S.pop();
        while (!S.empty() && gt[k] < S.top().st) {
          e[S.top().st] = k;
          S.pop();
        }
        while (!S.empty() && lt[k] > S.top().ed) S.pop();
        pt a = {k, lt[k]};
        S.push(a);
      }
    }
    stack<pt> S;
    for (i = n - 1, j = 0; i >= 0; --i) {
      if (e[i] < 0 || (!S.empty() && e[i] >= S.top().ed)) continue;
      pt a = {i, e[i]};
      S.push(a);
      ++j;
    }    
    printf("%d\n", j);
    while (!S.empty()) {
      printf("%d %d\n", S.top().st+1, S.top().ed+1);
      S.pop();
    }
  }
}
