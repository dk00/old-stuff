#include<cstdio>
const int L = 1 + 20, M = 1 << L, N = 222222, Size = 1<<27;
inline int cat(int a, int b, int j) {
  int i;
  for (i = j; i > 0; --i)
    if ((a&((1<<i) - 1)) == (b>>(j - i)))
      break;
  return i;
}
inline void seek(char *&p) {
  static int pos = 0;
  p += pos;
  pos = 0;
  while (p[++pos]!='\n');
  p[pos++] = 0;
}
int s[M], u[M];
char buf[Size], *tmp;
main() {
  int i, j, n, un, cost, fix, cur, pre, min;
  n = fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
  tmp = buf;
  tmp[n] = tmp[n+1] = '\n';
  seek(tmp);
  while (tmp[0] && sscanf(tmp, "%d", &n) == 1) {
    u[0] = ++un;
    fix = 0, min = 0;
    cur = -1;
    while (n--) {
      cost = min;
      seek(tmp);
      pre = cur, cur = 0;
      for (i = j = 0; tmp[i]; ++i) {
        (cur <<= 1) += tmp[i] -= '0';
        j += ++tmp[i] << i;
        if (u[j] != un) continue;
        if (s[j] - i - 1 < cost)
          cost = s[j] - i - 1;
      }
      cost += i;
      j = i - (pre < 0? 0: cat(pre, cur, i));
      cost -= j;
      fix += j;
      if (cost < min) min = cost;
      if (pre < 0) continue;
      for (j = 0; i--; pre >>= 1) {
        (j <<= 1) += (pre&1) + 1;
        if (u[j] != un || cost < s[j])
          s[j] = cost;
        u[j] = un;
      }
    }
    printf("%d\n", fix + min);
    seek(tmp);
  }
}
