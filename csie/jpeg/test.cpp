#include<cstdio>
int len[2][65536], val[2][65536];
void MakeTable(int id, int num[], int _v[]) {
  int i, j, k, x, q, c;
  int *l = len[id], *v = val[id];
  for (i = j = c = 0; i < 16; ++i) {
    c <<= 1;
    printf("%d %d\n", i, num[i]);
    for (k = 0; k < num[i]; ++k, ++c)
      for (x = 0; x < (1<<(15-i)); ++x) {
        v[(c<<(15-i))|x] = _v[j+k];
        l[(c<<(15-i))|x] = i+1;
        printf("%5d %5d %5d\n", (c<<(15-i))|x, c, i+1);
      }
    j += num[i];
  }
}
void printbin(int x, int n) {
  int i;
  for (i = 1<<(n-1); i > 0; i >>= 1)
    printf("%d", !!(i&x));
}
main() {
  int c, sz, i, j, k, s[333], bits[333], code[333];
  for (i = 1;i <= 16; ++i)
    scanf("%d", bits+i);
  k = 0, i = 1, j = 1;
  while (i <= 16) {
    if (j > bits[i])
      ++i, j = 1;
    else {
      s[k] = i;
      ++k;
      ++j;
      continue;
    }
  }
  s[k] = 0;
  for (i = 0; i < k; ++i)
    scanf("%d", &val[0][i]);
/*  for (i = 0; i < k; ++i)
    printf("%d ", s[i]);
  puts("");*/

  k = c = 0;
  sz = s[0];
  while (1) {
    code[k] = c;
    ++c;
    ++k;
    if (s[k] == sz) continue;
    if (s[k] == 0) break;
    while (sz < s[k])
      c <<= 1, ++sz;
  }
  for (i = 0; i < k; ++i) {
    printf("%d/%d ", (val[0][i]>>4)&0xF, val[0][i]&0xF);
    printbin(code[i], s[i]);
  }
  for (i = 0; i < 16; ++i)
    bits[i] = bits[i+1];
  //MakeTable(1, bits, val[1]);

}
