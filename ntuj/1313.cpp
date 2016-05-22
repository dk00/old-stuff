#include<queue>
#include<cstdio>
using namespace std;
const int N = 55, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, inf = 5000;
char map[N][N];
struct pt {
  int x, y, z;
};
int n, m, d[N][N][4];
bool valid(int x, int y, int z) {
  if (x < 0 || y < 0 || x >= n || y >= m || map[x][y] == '#')
    return false;
  int i, nx, ny;
  for (i = 0; i < 4; ++i) {
    if (i == z) continue;
    nx = x + dx[i];
    ny = y + dy[i];
    if (nx < 0 || ny < 0 || nx >= n || ny >= m || map[nx][ny] == '#')
      return false;
  }
  return true;
}
int dirc(int x, int y) {
  int i, j, nx, ny;
  for (i = 0; i < 4; ++i) {
    nx = x + dx[i];
    ny = y + dy[i];
    if (nx < 0 || ny < 0 || nx >= n || ny >= m || map[nx][ny] != map[x][y]) break;
  }
  for (j = i++; i < 4; ++i) {
    nx = x + dx[i];
    ny = y + dy[i];
    if (nx < 0 || ny < 0 || nx >= n || ny >= m || map[nx][ny] != map[x][y]) return -1;
  }
  return j;
}
main() {
  int i, j, k, x, y, z, nx, ny, T;
  pt ed;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j)
        for (k = 0; k < 4; ++k)
          d[i][j][k] = inf;
    for (i = 0; i < n; ++i)
      scanf("%s", map[i]);
    queue<pt> Q;
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j) {
        if (map[i][j] == '.' || map[i][j] == '#')
          continue;
        if ((k = dirc(i, j)) < 0) continue;
        if (map[i][j] == 'S') {
          d[i][j][k] = 0;
          Q.push((pt){i, j, k});
        }
        if (map[i][j] == 'E')
          ed.x = i, ed.y = j, ed.z = k;
      }
    while (!Q.empty()) {
      x = Q.front().x, y = Q.front().y, z = Q.front().z;
      Q.pop();
      for (i = 0; i < 4; ++i) {
        nx = x + dx[i], ny = y + dy[i];
        if (valid(nx, ny, z) && d[x][y][z] + 1 < d[nx][ny][z]) {
          d[nx][ny][z] = d[x][y][z] + 1;
          Q.push((pt){nx, ny, z});
        }
        if (i%2 != z%2 && valid(x, y, i) && d[x][y][z] + 1 < d[x][y][i]) {
          d[x][y][i] = d[x][y][z] + 1;
          Q.push((pt){x, y, i});
        }        
      }
    }
    if (d[ed.x][ed.y][ed.z] < inf)
      printf("%d\n", d[ed.x][ed.y][ed.z]);
    else puts("-1");
  }
}
