#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
struct pt {
  int x, y;
};
vector<pt> V;
int C, s[9][9], r[9][10], c[9][10], b[9][10], t[9][9];
int go() {
  ++C;
  int i, j, k, l, n, m, x, y, z, sum = 0;
  if (V.size() == 0) return 1;
  for (i = 0; i < 9; ++i)
    for (j = 0; j < 9; ++j)
      t[i][j] = 0;
  for (l = 0, x = -1; l < V.size(); ++l) {
    i = V[l].x, j = V[l].y;
    if (s[i][j]) continue;
    m = i/3*3+j/3;
    for (k = 1; k <= 9; ++k)
      if (!r[i][k] && !c[j][k] && !b[m][k])
        n = k, ++t[i][j];
    if (x < 0 || t[i][j] < t[V[x].x][V[x].y])
      x = l;
    if (t[i][j] < 0) return 0;
  }
  swap(V[x], V.back());
  i = V.back().x, j = V.back().y;
  V.pop_back();
  m = i/3*3+j/3;
  for (k = 1; k <= 9; ++k)
    if (!r[i][k] && !c[j][k] && !b[m][k]) {
      s[i][j] = k;
      r[i][k] = c[j][k] = b[m][k] = 1;
      sum += go();
      r[i][k] = c[j][k] = b[m][k] = 0;
      s[i][j] = 0;
    }
  V.push_back((pt){i, j});
  return sum;
}
int main() {
  char tmp[99];
  int i, j;
  while (scanf("%s", &tmp) > 0 && (tmp[0] != '0' || tmp[1])) {
    printf("%s ", tmp);
    for (i = 0; i < 9; ++i)
      for (j = 1; j <= 9; ++j)
        r[i][j] = c[i][j] = b[i][j] = 0;
    V.clear();
    for (i = 0; i < 9; ++i) {
      scanf("%s", tmp);
      for (j = 0; j < 9; ++j) {
        s[i][j] = tmp[j] - '0';
        r[i][s[i][j]] = 1;
        c[j][s[i][j]] = 1;
        b[i/3*3+j/3][s[i][j]] = 1;
        if (s[i][j] == 0)
          V.push_back((pt){i, j});
      }
    }
    C = 0;
    printf("%d\n", go());
  }
}
