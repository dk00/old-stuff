#include<set>
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
const int N = 10001;
struct Rule{
  Rule *p;
  int index, sub;
} s[N];
vector<Rule *> use[N];
vector<Rule *> collect;
int Parse(Rule& r, char s[]) {
  if (s[0] =='(') {
    int i = 0;
    char type;
    while (s[i] != ')') {
      if (s[i] !='(')
        type = s[i];
      ++i;
      Rule *pr = new Rule;
      collect.push_back(pr);
      pr->index = -1;
      pr->p = &r;
      pr->sub = 0;
      int j = Parse(*pr, s + i);
      ++r.sub;
      i += j;
    }
    if (type == 'O') r.sub = 1;
    return i + 1;
  }
  else {
    int i;
    sscanf(s, "%d", &i);
    use[i-1].push_back(&r);
    for (i = 0;'0' <= s[i] && s[i] <= '9';++i);
    return i;
  }
}
void Deduce(int r, queue<int>& q) {
  for (int i = 0; i < use[r].size(); ++i) {
    Rule *pr = use[r][i]->p;
    if (pr->index >= 0) {
      if (pr->sub != -99) q.push(pr->index);
      pr->sub = -99;      
      continue;
    }
    --pr->sub;
    while (pr->index < 0 && pr->sub <= 0) {
      if (pr->sub < 0) break;
      pr = pr->p;
      --pr->sub;
    }
    if (pr->sub == 0 && pr->index >= 0)
      q.push(pr->index);
  }
}
char tmp[999];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, n;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      use[i].clear();
    queue<int> q;
    for (i = 0; i < n; ++i) {
      scanf("%s", tmp);
      if (tmp[0] == 'C') {
        q.push(i);
        continue;
      }
      s[i].sub = 0;
      s[i].index = i;
      s[i].p = &s[i];
      Parse(s[i], tmp);      
    }
    int sum = 0;
    while (!q.empty()) {
      i = q.front();
      q.pop();
      ++sum;
      Deduce(i, q);
    }
    printf("%d\n", sum);
  }
}
