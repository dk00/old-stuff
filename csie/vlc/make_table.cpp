#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 999, M = 9999, L = 99, B = 4;
struct Code {
  int l, i;
  long long c;
  string s;
  bool operator<(Code x) const {
    for (long long i = 1; ; i*=2)
      if ((c&i)!=(x.c&i))
        return (c&i)<(x.c&i);
    return false;
  }
} s[N];
struct pt {
  int x, y;
};
char name[L], symbol[N][L], t0[L], t1[L];
inline int rev(int d, int t) {
  int i, r = 0;
  for (i = 0; i < d; ++i) {
    r = (r<<1)|(t&1);
    t >>= 1;
  }
  return r;
}
vector<pt> tmp;
int go(int n, int p, Code s[], vector<int>& t) {
  int i, j, k, d, x, o, n1, m0 = (1<<B) - 1;
  vector<int> c;
  for (n1 = 0; n1 < n; ++n1) {
    j = rev(B, (s[n1].c>>p)&m0);
    if (s[n1].l - p > B || (c.size() > 0 && j < c[n1-1]))
      break;
    c.push_back(j);
    d = s[n1].l - p;
  }
  for (i = 0; i < n1; ++i)
    c[i] >>= B - d;

  if (n1 < n && j > 0) x = j>>(B-d);
  else x = (1<<d);
  o = t.size();
  for (i = j = 0; j < x; ++j) {
    if (i+1 < n1 && c[i+1] <= j) ++i;
    s[i].i = o+rev(s[i].l-p, s[i].c>>p);
    t.push_back(rev(s[i].l-p, s[i].c>>p)|(1<<s[i].l-p));
  }
  for (j = x, k = t.size(); j <(1<<d); ++j)
    t.push_back(-1);
  o = t.size();
  for (j = x; j <(1<<d); ++j) {
    tmp.push_back((pt){k, t.size()-o});
    x = go(n-n1, p+B, s+n1, t);
    t[k++] = -(x&3);  //XXX lg(B)
    n1 += x>>2;
  }
  return (n1<<2)|(d-1);
}

main() {
  int i, j, n, m;
  while (scanf("%s", name) == 1) {
    puts(name);
    for (n = 0; scanf("%s %*d %s", t0, t1) == 2; ++n) {
      s[n].s = t0;
      if (t0[0] == '-') break;
      long long c = 0;
      for (i = 0; t1[i]; ++i)
        c |= (t1[i] - '0')<<i;
      s[n].l = i;
      s[n].c = c;
    }
    sort(s, s+n);
    vector<int> t;
    tmp.clear();
    go(n, 0, s, t);
    printf("%d\n", t.size());
    for (i = 0; i < t.size(); ++i)
      printf("%2d ", t[i]);
    puts("");
    printf("%d\n", n + tmp.size());
    for (i = 0; i < tmp.size(); ++i)
      printf("%d %d\n", tmp[i].x, tmp[i].y);
    puts("");
    for (i = 0; i < n; ++i)
      printf("%d %d %s\n", s[i].i, i, s[i].s.c_str());
  }
}

/*
           +-----------------------+
           |                       |
     +-----------+           +-----------+
     |           |           |           |
     |        +-----+     +-----+     +-----+
     |        |     |     |     |     |     |
+---------+ +---+ +---+ +---+ +---+ +---+ +---+
 4  4  4  4 10 10 11 11 12 12 13 13 14 14 30  a 

                       a
           +-----------------------+
           |                       |
           |                 +-----------+
           |                 |           |
           |                 |        +-----+
           |                 |        |     |  
           |                 |        |   +---+
+---------------------+ +---------+ +---+ |   | 
 2  2  2  2  2  2  2  2  6  6  6  6 14 14 30  b

  b
+---+
 2  2

K6
2 00
2 01
3 100
4 1010
4 1011
5 11000
5 11001
5 11010
5 11011
6 111000
6 111001
6 111010
6 111011
7 1111000
7 1111001
7 1111010
8 11110110
8 11110111
8 11111000
8 11111001
9 111110100
9 111110101
9 111110110


 */
