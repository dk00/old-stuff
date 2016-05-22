const int N = 50000;
typedef char CharType;
void rsort(int x[], int t0[], int t1[], int n, int m) {
  static int num[N];
  int i;
  for (i = 0; i <= m; ++i) num[i] = 0;
  for (i = 0; i < n; ++i) ++num[x[t0[i]]+1];
  for (i = 1; i <= m; i++) num[i] += num[i-1];
  for (i = 0; i < n; i++) t1[num[x[t0[i]]]++] = t0[i];
}
void SuffixArray(const CharType text[], int t[], int n, int m) {
  int i, j, k;
  static int s[N*2], tmp[N+2];
  for (i = 0; i < n; ++i) s[i] = text[i], t[i] = i;
  for (i = t[n] = n; i < n*2; ++i) s[i] = 0;
  for (i = 1; i < n; i *= 2) {
    rsort(s+i, t, tmp, n, m);
    rsort(s, tmp, t, n, m);
    for (j = 0; j < n; ++j) tmp[j] = s[j];
    for (j = 0, m = 1; j < n; ++j) {
      s[t[j]] = m;
      if (tmp[t[j]] != tmp[t[j+1]] || tmp[t[j]+i] != tmp[t[j+1]+i])m++;
    }
  }
}
int x[N];
void go(const CharType s[], const int t[], int d[], int n) {
  int i, j, k;
  for (i = 0; i < n; ++i) x[t[i]] = i;
  for (i = j = 0; i < n; ++i) {
    if (x[i] == n-1) {
      j = d[x[i]] = 0;
      continue;
    }
    k = t[x[i]+1];
    while (s[i+j] == s[k+j])
      j++;
    d[x[i]] = j;
    if (j > 0) --j;
  }
}
#include<stack>
using namespace std;
void find (int n, int t[], int d[], int lt[], int gt[]) {
  int i;
  stack<int> S;
  for (i = 0; i < n; ++i) {
    while (!S.empty() && d[i] < d[S.top()]) {
      lt[S.top()] = i;
      S.pop();
    }
    S.push(i);
  }
  while (!S.empty()) {
    lt[S.top()] = S.top();
    S.pop();
  }
  for (i = 0; i < n; ++i) {
    while (!S.empty() && t[i] > t[S.top()]) {
      gt[S.top()] = i;
      S.pop();
    }
    S.push(i);
  }
  while (!S.empty()) {
    gt[S.top()] = S.top();
    S.pop();
  }
}
CharType s[N];
int n, d[N], t[N], lt[N], gt[N];
#include<cstdio>
main() {
  int i, j, k, m, len, pos;
  while (scanf("%d %s", &m, s) == 2 && m > 0) {
    for (n = 0; s[n]; ++n)
      s[n] -= 'a'-1;
    SuffixArray(s, t, n, 'z'-'a'+1);
    for (i = 0; i < n; ++i)
      s[i] += 'a'-1;
    go(s, t, d, n);
    find(n, t, d, lt, gt);
    len = -1;
    for (i = j = k = 0; i < n; ++i) {
      if (j < i) j = i;
      if (k < i) k = i;
      while (lt[j] > j && lt[j] < i+m-1) j = lt[j];
      while (gt[k] > k && gt[k] < i+m) k = gt[k];
      if (d[j] > len) {
        len = d[j];
        pos = t[k];
      }
      else if (d[j] == len && pos < t[k])
        pos = t[k];
    }
    if (m == 1)
      len = n, pos = 0;
    if (len > 0) printf("%d %d\n", len, pos);
    else puts("none");
  }
}
