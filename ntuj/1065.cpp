#include<queue>
#include<cstdio>
using namespace std;
const int N = 100005;
struct pt {
  int pos;
  double val;
  bool operator<(pt a) const {return val > a.val;}
};
int n, m, st, ed, s[N], next[N];
double Max, t[N];
bool test0(double x) {
  int i;
  for (i = 0; i < n; ++i) t[i] = s[i] - i*x;
  double low = t[0];
  for (i = 0; i + m < n; ++i) {
    if (t[i] < low) low = t[i];
    if (t[i+m] >= low) return true;
  }
  return false;
}
bool test(double x) {
  int i, j;
  priority_queue<pt> H;
  for (i = j = 0; i < n; ++i) {
    if (i - m >= 0) H.push((pt){i-m, t[i-m]});
    t[i] = s[i] - i*x;
    while (!H.empty() && t[i] >= H.top().val) {
      next[H.top().pos] = i;
      H.pop();
    }
  }
  while (!H.empty()) {
    next[H.top().pos] = n;
    H.pop();
  }
  bool flag = false;
  for (i = 0; i + m < n; ++i) {
    j = next[i];
    if (j >= n) continue;
    flag = true;
    if (x > Max || (x >= Max && j - i < ed - st) 
        ||  (x >= Max && j - i == ed - st && i < st))
      st = i, ed = j, Max = x;
  }
  return flag;
}
char tmp[N*2];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i;
    scanf("%d %d", &n, &m);
    scanf("%s", tmp);
    s[0] = 0;
    ++n;
    for (i = 1; i < n; ++i)
      s[i] = s[i-1] + tmp[i-1] -'0';
    Max = -1;
    double lb = 0, ub = 1, mid;
    while (ub - lb > 1e-13) {
      mid = (lb + ub)/2;
      if (test0(mid)) lb = mid;
      else ub = mid;
    }
    test(mid - 1e-12);
    printf("%d %d\n", st+1, ed);
  }
}
