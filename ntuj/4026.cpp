#include<map>
#include<cstdio>
#include<string>
using namespace std;
int k;
string dec(long long v) {
  string r = "";
  for (int i = 0; i < k; ++i, v /= 7)
    r = ((char)(v%7 + 'A')) + r;
  return r;
}
char tmp[999], tmp1[999];
main() {
  int i, j, n, m, q0, p0, q1, p1, C = 1;
  long long v, M;
  while (scanf("%d %d %d", &n, &m, &k) == 3 && n) {
    map<long long, int> P, Q;
    for (j = 0, M = 1; j < k; ++j)
      M *= 7;
    for (i = 0; i < n; ++i) {
      scanf("%s %s", tmp, tmp1);
      for (v = j = 0; tmp[j] && j < k; ++j)
        v = tmp[j] - 'A' + v*7%M;
      map<long long, int> R;
      for (; tmp[j-1]; ++j) {
        if (R.count(v)) continue;
        R[v] = 1;
        ++P[v];
        if (tmp1[0] == 'Y')
          ++Q[v];
        v = tmp[j] - 'A' + v*7%M;
      }
    }
    string ans = "No solution";
    map<long long, int>::iterator p;
    for (p = P.begin(); p != P.end(); ++p) {
      if (p->second < m) continue;      
      q1 = Q[p->first];
      p1 = p->second;
      //printf("%s %d/%d\n", dec(p->first).c_str(), q1, p1);
      if (ans == "No solution" || q1*p0 < q0*p1 || (q1*p0 == q0*p1 && p1 > p0)) {
        q0 = q1, p0 = p1;
        ans = dec(p->first);
      }
    }
    printf("Case %d: %s\n", C++, ans.c_str());
  }
}
