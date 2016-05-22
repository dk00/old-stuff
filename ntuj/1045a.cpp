#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 105;
struct pt {
  int x, y;
  bool operator<(pt a) const{
    if (x != a.x) return x < a.x;
    return y < a.y;
  }
  pt operator-(pt a) {
    pt tmp = *this;
    tmp.x -= a.x;
    tmp.y -= a.y;
    return tmp;
  }
  int operator*(pt a) {
    return x*a.y - y*a.x;
  }
}O, s0[N], s1[N];

bool cmp(pt a, pt b) {
  return (a - O)*(b - O) < 0;
}
bool cmp1(pt o, pt a, pt b) {
  return (a - o)*(b - o) < 0;
}
inline int area(pt a, pt b, pt c) {
  return a.x*b.y + b.x*c.y + c.x*a.y
    - a.y*b.x - b.y*c.x - c.y*a.x;
}
inline bool test(vector<int>& H, pt a) {
  int i, sum0 = 0, sum1 = 0, tmp = H.back();
  printf("%d %d\n", a.x, a.y);
  for (i = 0; i < H.size(); ++i) {
    sum0 += s0[tmp].x * s0[H[i]].y;
    sum0 -= s0[tmp].y * s0[H[i]].x;
    sum1 += area(s0[tmp], s0[H[i]], a);
    tmp = H[i];
  }
  printf("%d %d\n", sum0, sum1);
  return abs(sum0) == abs(sum1);
}
int main() {
  int i, n0, n1;
  while (scanf("%d %d", &n0, &n1) == 2 && n0 + n1) {
    bool no = false;
    for (i = 0; i < n0; ++i)
      scanf("%d %d", &s0[i].x, &s0[i].y);
    for (i = 0; i < n1; ++i)
      scanf("%d %d", &s1[i].x, &s1[i].y);
    sort(s0, s0+n0);
    O = s0[0];
    sort(s0+1, s0+n0, cmp);
    vector<int> H;
    for (i = 0; i < n0 ; ++i) {
      while(H.size() > 1 && !cmp1(s0[H[H.size() - 2]], s0[H.back()], s0[i]))
        H.pop_back();
      H.push_back(i);
    }
    for (i = 0; !no && i < n1; ++i)
      if (test(H, s1[i])) no = true;
    if (no) {
      puts("NO");
      continue;
    }
    for (i = 0; i < n0 || i < n1; ++i)
      swap(s0[i], s1[i]);
    swap(n0, n1);
    sort(s0, s0+n0);
    O = s0[0];
    sort(s0+1, s0+n0);
    for (i = 0; i < n0 ; ++i) {
      while(H.size() > 1 && !cmp1(s0[H[H.size() - 2]], s0[H.back()], s0[i]))
        H.pop_back();
      H.push_back(i);
    }
    for (i = 0; !no && i < n1; ++i)
      if (test(H, s1[i])) no = true;
    if (no) puts("NO");
    else puts("YES");
  }
}
