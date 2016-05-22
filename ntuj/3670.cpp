#include<queue>
#include<cstdio>
using namespace std;
const int N = 22, inf = 220000, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int c[N][N], d[N][N][N];
struct pt{
  int x, y, z;
};
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, n, m, L;
    scanf("%d %d %d", &n, &m, &L);
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j) {
        scanf("%d", &c[i][j]);
        for (k = 0; k <= L; ++k)
          d[i][j][k] = inf;
      }
    queue<pt> Q;
    Q.push((pt){0, 0, 0});
    d[0][0][0] = 0;
    while (!Q.empty()) {
      int x = Q.front().x, y = Q.front().y, z = Q.front().z;
      Q.pop();
      for (i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i], nz = z;
        if (nx < 0 || nx >= n || ny < 0 || ny >= m)
          continue;
        if (c[nx][ny]) ++nz;
        else nz = 0;
        if (nz > L || d[x][y][z] + 1 >= d[nx][ny][nz]) continue;
        d[nx][ny][nz] = d[x][y][z] + 1;
        Q.push((pt){nx, ny, nz});
      }
    }
    if (d[n-1][m-1][0] < inf)
      printf("%d\n", d[n-1][m-1][0]);
    else
      puts("-1");
  }
}
