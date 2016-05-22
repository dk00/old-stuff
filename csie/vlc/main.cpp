#include<map>
#include<cstdio>
#include<vector>
#include<algorithm>
#include"codes.h"
using namespace std;

class Reader {
  FILE *fp;
public:
  bool init(const char *name) {
    FILE *fp = fopen(name, "r");
    return fp != NULL;
  }
};

class Writer {
  FILE *fp;
public:
  bool init(const char *name) {
    FILE *fp = fopen(name, "r");
    return fp != NULL;

  }
};

class Decoder {
  vector<int> p;
  vector<int> super;
  vector<string> symbol;
public:
  bool init(vector<Code> c, int L = 4) {
    int i, j, k, l, st = 0;
    for (i = 0; i < c.size(); ++i) {
      for (j = k = 0; j < c[i].len; ++j)
        k = k*2 + c[i].code[j];
      k <<= (L-c[i].len);
      j = 1<<(L-c[i].len);
      while (j--) {
        l = st + (k<<(L-c[i].len)) + j;
        p[l] = k|(1<<c[i].len);
      }
      symbol[st+k] = c[i].symbol;
    }
  }
  void decode(Reader r, Writer w) {
  }
};

bool cmp(const Code& a, const Code& b) {
  int i;
  if (a.len != b.len) return a.len < b.len;
  for (i = 0; a.code[i] == b.code[i]; ++i);
  return a.code[i] < b.code[i]; 
}

const int BufLen = 999;
const char *tostr(int n, bitset<256> s) {
  static char tmp[BufLen];
  int i;
  for (i = 0; i < n; ++i)
    tmp[i] = '0' + s[i];
  tmp[i] = 0;
  return tmp;
}
bool read_code(FILE *fp, char name[], vector<Code>& c) {
  if (fscanf(fp, "%s", name) != 1) return false;
  Code tmp;
  char symbol[BufLen], code[BufLen];
  c.clear();
  while (fscanf(fp, "%s %*s %s", symbol, code) == 2 && code[0] != '-') {
    tmp.code = 0;
    for (tmp.len = 0; code[tmp.len]; ++tmp.len) {
      tmp.code[tmp.len] = (code[tmp.len] - '0');
    }
    tmp.symbol = symbol;
    c.push_back(tmp);
  }
  sort(c.begin(), c.end(), cmp);
  puts(name);
  for (int i = 0; i < c.size(); ++i)
    printf("%s %s\n", c[i].symbol.c_str(), tostr(c[i].len, c[i].code));
  return true;
}
void init_codes(map<string, vector<Code> >& H) {
  FILE *fp = fopen("codes.txt", "r");
  char name[BufLen];
  vector<Code> c;
  while (read_code(fp, name, c))
    H[name] = c;
  fclose(fp);
}

main(int argc, char **argv) {
  map<string, vector<Code> > H;
  //init_codes(H);

  return 0;
  /*argv[1]:  table name
    argv[2]:  compressed
    argv[3]:  decoded */
  if (argc < 4) {
    //XXX: usage
    puts("!");
    return 0;
  }
  Reader r;
  Writer w;
  Decoder d;
  
  r.init(argv[2]);
  w.init(argv[3]);
  //XXX if table name in H
  d.init(H[argv[1]]);
  d.decode(r, w);
}
