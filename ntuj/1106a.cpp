#include<cstdio>
const int N = 1000005 + 160*80;
inline void radixsort(int x[], int t0[], int t1[], int n , int m) {
  static int num[N];
  int i;
  for (i = 0; i <= m; ++i) num[i] = 0;
  for (i = 0; i < n; ++i) ++num[x[t0[i]]+1];
  for (i = 1; i <= m; ++i) num[i] += num[i-1];
  for (i = 0; i < n; i++) t1[num[x[t0[i]]]++] = t0[i];
}
inline void SuffixArray(const char text[], int t[], int n, int m) {
  int i, j, k;
  static int s[N*2], tmp[N+2];
  for (i = 0; i < n; ++i) s[i] = text[i], t[i] = i;
  for (i = t[n] = n; i < n*2; ++i) s[i] = 0;
  for (i = 1; i < n; i *= 2) {
    radixsort(s+i, t, tmp, n, m);
    radixsort(s, tmp, t, n, m);
    for (j = 0; j < n; ++j) tmp[j] = s[j];
    for (j = 0, m = 1; j < n; ++j) {
      s[t[j]] = m;
      if (tmp[t[j]] != tmp[t[j+1]] || tmp[t[j]+i] !=  tmp[t[j+1]+i]) m++;
    }
  }
}
int x[N];
inline void depth(const char s[], const int t[], int d[], int n) {
  int i, j, k;
  for (i = 0; i < n; ++i) x[t[i]] = i;
  for (i = j = 0; i < n; ++i) {
    if (x[i] == n-1) {
      j = d[x[i]] = 0;
      continue;
    }
    k = t[x[i]+1];
    while (s[i+j] == s[k+j])
      ++j;
    d[x[i]] = j;
    if (j > 0) --j;
  }
}
char s[N];
int t[N], d[N], num[N], next[N], id[N], pos[200], len[200], count[200];
#include<stack>
using namespace std;
struct pt {
  int st, len;
};
main() {
  int i, j, n, m;
  for (i = 0; i < N; ++i) id[i] = -1;
  while (scanf("%d", &n) == 1 && n) {
    for (i = m = 0; i < n; ++i) {
      count[i] = 0;
      id[m] = i;
      pos[i] = m;
      scanf("%s", s + m);
      while (s[m]) ++m;
      len[i] = m - pos[i];
      s[m++] = '$';
    }
    scanf("%s", s+m);
    while (s[m]) num[m++] = 1;
    s[m++] = '}';
    SuffixArray(s, t, m, 256);
    depth(s, t, d, m);
    for (i = 1; i <= m; ++i)
      num[t[i]] += num[t[i-1]];
/*    for (i = 0; i < m; ++i)
      printf("%2d %d %d %s\n", id[t[i]], d[i], num[t[i]], s+t[i]);*/
    stack<pt> H;
    for (i = 0; i < m; ++i) {
      while (!H.empty() && d[i] < H.top().len) {
        count[id[t[H.top().st]]] = num[t[i]] - num[t[H.top().st]];
        H.pop();
      }
      if (id[t[i]] >= 0)
        H.push((pt){i, len[id[t[i]]]});
    }
    while (!H.empty()) {
      count[id[H.top().st]] = num[i-1] - num[H.top().st];
      H.pop();
    }    
    for (i = 0; i <= m; ++i) num[i] = 0;
    for (i = j = 0; i < n; ++i)
      if (count[i] > j) j = count[i];
    printf("%d\n", j);
    for (i = 0; i < n; ++i) {
      id[pos[i]] = -1;
      if (count[i] == j) {
        s[pos[i]+len[i]] = 0;
        puts(s+pos[i]);
      }
    }
  }
}
