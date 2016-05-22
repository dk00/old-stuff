#include<cstdio>
main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d", &n, &m, &x);
    for (i = 0; i < n; ++i)
      for (j = d[i] = 0; j < n; ++j)
        c[i][j] = 0;
    while (m--) {
      scanf("%d %d", &i, &j);
      ++d[i];
      c[i][j] = 1;
    }
    queue<int> Q;
    for (i = 0; i < n; ++i)
      if (d[i] == 0) Q.push(i);
    while (!Q.empty()) {
      i = Q.front();
      for (j = 0; j < n; ++j)
        if (c[j][i] && --d[j] == 0)
          Q.push(j);
      s[i] = 0;
      for (j = 0; j < n; ++j)
        if (c[i][j] && s[j])
    }
  }
}
