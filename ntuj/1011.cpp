#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1024;
struct pt {
  int x, y, v;
  bool operator<(pt a)const {
    if (y != a.y) return y > a.y;
    return x < a.x;
  }
} s[N], t[N];
bool cmp(pt a, pt b) {
  if (a.x != b.x) return a.x < b.x;
  return a.y > b.y;
}
int num[N];
int tmp[N];
int Disc(int n, pt s[]) {
  int i, j;
  for (i = j = 0; i < n; ++i) {
    tmp[j++] = s[i].x;
    tmp[j++] = s[i].y;
  }
  sort(tmp, tmp+j);
  map<int, int> H;
  for (i = 0; i < j; ++i)
    if (H.count(tmp[i]) == 0)
      H[tmp[i]] = H.size();
  for (i = 0; i < n; ++i) {
    s[i].x = H[s[i].x];
    s[i].y = H[s[i].y];
  }
  sort(s, s+n, cmp);
  for (i = 0; i < 1024; ++i) num[i] = 0;
  return H.size() + 1;
}
int h[N];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, l, n, m, nt, a, eq;
    scanf("%d", &n);
    for (i = eq = 0; i < n; ++i) {
      scanf("%d %d", &s[i].x, &s[i].y);      
      if (s[i].x == s[i].y)
        --i, --n, ++eq;
    }
    m = Disc(n, s);
    priority_queue<pt> H;
    s[n].x = m;
    for (i = a = nt = 0; i <= n; ++i) {
      printf("> %d %d\n", s[i].x, s[i].y);
      while (!H.empty() && s[i].x >= H.top().y) {
        pt tmp = H.top();
        H.pop();
        printf("< %d %d\n", tmp.x, tmp.y);
        tmp.v = 0;
        for (k = nt-1, l = m-1; k >= 0; --k) {
          for (; l > t[k].y; --l)
            if (num[l] > num[l-1])
              num[l-1] = num[l];
          if (num[t[k].y] + t[k].v > num[t[k].x])
            num[t[k].x] = num[t[k].y] + t[k].v;
          if (t[k].x >= tmp.x && num[t[k].x] > tmp.v)
            tmp.v = num[t[k].x] + 1;
        }        
        while (!H.empty() && tmp.x == H.top().x && tmp.y == H.top().y)
          ++tmp.v, H.pop();
        num[tmp.x] = tmp.v;
        j = tmp.v + h[tmp.x];
        if (j > a) a = j;
        t[nt++] = tmp;        
      }
      h[s[i].x] = a;
      H.push(s[i]);
    }
    printf("%d\n", a + eq);
  }
}
