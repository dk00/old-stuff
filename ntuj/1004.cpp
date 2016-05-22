#include<map>
#include<cstdio>
#include<string>
using namespace std;
const int N = 60000;
int un, l[N], r[N], len[N], u[N];
string tag[N];
char tmp[N];
map<string, int> H;
int go(int d, char s[]) {
  int i, j, k;
  for (i = 0; s[i] && s[i] != '(' && s[i] != ',' && s[i]!=')'; ++i) ;
  if (!s[i] || s[i] == ')' || s[i] == ',') {
    s[i] = 0;
    if (H.count(s)) return H[s];
    l[d] = r[d] = -1;
    len[d] = i;
    tag[d] = s;
    return H[s] = d;
  }
  s[i] = 0;
  int x = H.size();
  j = go(d + 1, s+i+1);
  i += len[j] + 1;
  k = go(d - x + H.size() + 1, s+i+1);
  i += len[k] + 2;
  sprintf(tmp, "%s %d %d", s, j, k);
  if (H.count(tmp)) return H[tmp];
  H[tmp] = d;
  tag[d] = s;
  l[d] = j;
  r[d] = k;
  len[d] = i;
  return d;
}
void go(int v) {
  if (u[v] == un) {
    printf("%d", v+1);
    return;
  }
  u[v] = un;
  printf("%s", tag[v].c_str());
  if (l[v] >= 0) {
    printf("(");
    go(l[v]);
    printf(",");
    go(r[v]);
    printf(")");
  }
}
char t[N*20];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    H.clear();
    scanf("%s", t);
    go(0, t);
    ++un;
    go(0);
    puts("");
  }
}
