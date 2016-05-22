#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 105, M = 105,
      dx[] = {-1, -1, 0, 1, 1, 1, 0, -1}, 
      dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
struct pt {
  int x, y;
  bool operator<(pt a) const {
    if (x != a.x) return x < a.x;
    return y < a.y;
  }
  void operator-=(pt a) {
    x -= a.x;
    y -= a.y;
  }
};
int n, m;
char s[N][M];
vector<pt> s0;
map<vector<pt>, char> H;
void go(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= m || s[x][y] != '1')
    return;
  s[x][y] = 0;
  s0.push_back((pt){x, y});
  for (int i = 0; i < 8; ++i)
    go(x+dx[i], y+dy[i]);
}
void fix(vector<pt>& t) {
  sort(t.begin(), t.end());
  pt m;
  m.x = t[0].x, m.y = t[0].y;
  for (int i = 0; i < t.size(); ++i) {
    if (t[i].x < m.x) m.x = t[i].x;
    if (t[i].y < m.y) m.y = t[i].y;
  }
  for (int i = 0; i < t.size(); ++i)
    t[i] -= m;
}
void rotate(vector<pt>& t) {
  for (int i = 0; i < t.size(); ++i) {
    int ny = N - t[i].x, nx = t[i].y;
    t[i].x = nx;
    t[i].y = ny;
  }
  fix(t);
}
void mirror(vector<pt>& t) {
  for (int i = 0; i < t.size(); ++i)
    t[i].y = -t[i].y;
  fix(t);
}
int Label(const vector<pt>& s) {
  vector<pt> tmp = s;
  fix(tmp);
  if (H.count(tmp)) return H[tmp];
  for (int i = 0; i < 3; ++i) {
    rotate(tmp);
    if (H.count(tmp)) return H[tmp];
  }
  rotate(tmp);
  mirror(tmp);
  if (H.count(tmp)) return H[tmp];
  for (int i = 0; i < 3; ++i) {
    rotate(tmp);
    if (H.count(tmp)) return H[tmp];
  }
  return H[tmp] = H.size() - 1;
}
using namespace std;
char label[99];
main() {
  int i, j, k, l;
  for (n = 0, i = 'A'; i <= 'Z'; ++i)
    label[n++] = i;
  for (i = 'a'; i <= 'z'; ++i)
    label[n++] = i;
  while (scanf("%d %d", &n, &m) == 2 && n+m) {
    H.clear();
    for (i = 0; i < n; ++i)
      scanf("%s", s[i]);
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j)
        if (s[i][j] == '1') {
          s0.clear();
          go(i, j);
          l = Label(s0);
          for (k = 0; k < s0.size(); ++k)
            s[s0[k].x][s0[k].y] = label[l];
        }
    printf("%d\n", H.size());
    for (i = 0; i < n; ++i) puts(s[i]);
  }
}
