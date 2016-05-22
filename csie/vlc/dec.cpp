#include"io.h"
#include<string>
#include<cstdio>
using namespace std;
const int N = 22222, M = 33333, B = 4, TN = 33, L = 99;
string _sym[TN][N], name[TN];
int tn, n, m, _s[TN][M], _t[TN][M];
inline unsigned cl(unsigned x) {
  int i;
  for (i = 0; (2<<i) <= x; ++i);
  return i;
}
int decode(const char tname[], Reader r, Writer w) {
  int i, j, k, l, x, v, *s, *t;
  string *symbol;
  for (i = 0; i < tn; ++i)
    if (name[i] == tname) break;
  if (i >= tn) {
    printf("Unknown table %s\n", tname);
    return -1;
  }
  printf("Using table %s\n", tname);
  s = _s[i], t = _t[i], symbol = _sym[i];

  for (i = v = l = x = 0, j = B; !r.end; ) {
    v |= r.read(j);
    if (r.end) break;
    k = s[i+v];
    printf("S-tree offset: %4d SGH-tree index: %4d sign: %d\n", i, i+v, k <=0);
    if (k <= 0) {
      i += (1<<B) + t[i+v];
      j = 1 - k;
      x = B - j;
      v = 0;
      continue;
    }
    l = cl(k);
    v <<= l;
    v &= (1<<B) - 1;
    k &= ~(1<<l);
    printf("magnitude: %4d decoded: %s\n", k|(1<<l), symbol[t[i+k]].c_str());
    w.write(symbol[t[i+k]].c_str());
    i = 0, j = l;
    j += x, x = 0;
  }
}

bool load_table() {
  FILE *fp = fopen("tables.txt", "r");
  int i, j, *s, *t;
  string *symbol;
  char tmp[L];
  puts("load table");
  for (tn = 0; fscanf(fp, "%s", tmp) == 1; ++tn) {
    name[tn] = tmp;
    s = _s[tn], t = _t[tn], symbol = _sym[tn];
    fscanf(fp, "%d", &m);
    for (i = 0; i < m; ++i)
      fscanf(fp, "%d", s+i);
    fscanf(fp, "%d", &n);
    for (i = 0; i < n; ++i) {
      fscanf(fp, "%d", &j);
      fscanf(fp, "%d", t+j);
      if (s[j] > 0) {
        fscanf(fp, "%s", tmp);
        if (symbol[t[j]].length() < 1)
          symbol[t[j]] = tmp;
      }
    }
    printf("loaded table %s\n", name[tn].c_str());
  }
  fclose(fp);
}

main(int argc, char **argv) {
  //XXX table name, compressed, decoded
  load_table();
  Reader r;
  Writer w;
  r.init(argv[2]);
  w.init(argv[3]);
  decode(argv[1], r, w);
  r.close();
  w.close();
}
