#include<map>
#include<string>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 15555;
struct pt {
  int t;
  string name;
  bool operator<(const pt& a) const {
    if (t != a.t) return t < a.t;
    return name < a.name;
  }
} s[N];
char tmp[22];
string name[N];
int m, s0[N], s1[N], t[N];
map<string, int> H;
int find(string tmp) {
  if (H.count(tmp))
    return H[tmp];
  name[m] = tmp;
  t[m] = 0;
  return H[tmp] = m++;
}
void go(int i, int x) {
  if (x < 0) return;
  if (t[x] == 0) t[x] = i + 40;
}
main() {
  int i, j, n0, n1, T;
  scanf("%d", &T);
  while (T--) {
    m = 0;
    H.clear();
    for (i = 0; i < N; ++i)
      s0[i] = s1[i] = -1;

    for (n0 = j = 0; scanf("%s", tmp) && tmp[0] != '-'; ++n0) {
      j += strlen(tmp);
      s0[j] = find(tmp);
    }
    n0 = j + 1;
    for (n1 = j = 0; scanf("%s", tmp) && tmp[0] != '-'; ++n1) {
      j += strlen(tmp);
      s1[j] = find(tmp);
    }
    n1 = j + 1;
    for (i = 0; i < n0 && i < n1; ++i) {
      if (s0[i] == s1[i]) continue;
      go(i, s0[i]);
      go(i, s1[i]);
    }
    for (;i < n0; ++i) go(i, s0[i]);
    for (;i < n1; ++i) go(i, s1[i]);

    for (i = 0; i < m; ++i) {
      s[i].t = t[i];
      s[i].name = name[i];
    }
    sort(s, s + m);
    for (i = 0; i < m && s[i].t <= 40; ++i);
    for (; i < m; ++i)
      printf("%s %d\n", s[i].name.c_str(), s[i].t);
    puts("-");
  }
}
