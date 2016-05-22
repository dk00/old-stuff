#include<cstdio>
const int N = 300, dx[] = {-1, -1, -1, 0, 1, 1, 1, 0},
  dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int n, m;
char s[N][N];
bool valid(int x, int y) {return (x >= 0 && x < n && y >= 0 && y < m);}
void go(int x, int y) {
  if (s[x][y] == ' ') return;
  if (s[x][y] == '*') return;
  if (s[x][y] == '!') {
    s[x][y] = ' ';
    return;
  }
  s[x][y] = ' ';
  for (int i = 0; i < 8; ++i)
    if (valid(x+dx[i], y+dy[i])) go(x+dx[i], y+dy[i]);
}
main() {
  int i, j, k, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
      scanf("%s", s[i]);
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j)
        if (s[i][j] == '*')
          for (k = 0; k < 8; ++k) {
            int nx = i+dx[k], ny = j+dy[k];
            if (valid(nx, ny) && s[nx][ny] != '*') s[nx][ny] = '!';
          }
    for (i = k = 0; i < n; ++i)
      for (j = 0; j < m; ++j)
        if (s[i][j] == '.')
          ++k, go(i, j);
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j)
        if (s[i][j] == '!') ++k;
    printf("%d\n", k);
  }
}
