#include<map>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 900, M = 900;
struct pt {
  int v, c;
};
struct State {
  int n, d;
  pt s[N];
  bool operator<(const State& a)const {
    if (n != a.n) return n < a.n;
    for (int i = 0; i < n; ++i) {
      if (s[i].v != a.s[i].v)
        return s[i].v < a.s[i].v;
      if (s[i].c != a.s[i].c)
        return s[i].c < a.s[i].c;
    }          
  }
  bool operator^=(const State& a) {
    int i, j, n0 = n;
    pt tmp[N];
    for (i = 0; i < n; ++i) tmp[i] = s[i];
    for (i = j = 0; i < n; ++i) {
      for (;j < a.n && a.s[j].v != tmp[i].v; ++j)
        s[j] = a.s[j];
      if (j >= a.n) return false;
      s[j] = a.s[j];      
      s[j].c -= tmp[i].c;
      ++j;
    }
    n = a.n;
    for (i = j = 0; i < n; ++i)
      if (s[i].c > 0) s[j++] = s[i];
    n = j;
    return true;
  }
  void ins(int v) {
    int i, j;
    for (i = 0; i < n && v > s[i].v; ++i);
    if (i < n && v == s[i].v) {
      ++s[i].c;
      return;
    }
    for (j = n++; j > i; --j)
      s[j] = s[j-1];
    s[i].v = v;
    s[i].c = 1;
  }
  void rm(int i) {
    if (--s[i].c > 0) return;
    --n;
    for (; i < n; ++i)
      s[i] = s[i+1];
  }
};
int Count[M];
void go(int n) {
  int i, j;
  for (i = 2; i <= n; ++i)
    while (n%i == 0) {
      ++Count[i];
      n/=i;
    }
}
int go(pt s[], int c[]) {
  int i, n = 0;
  sort(c, c+M);
  for (i = 0; i < M; ++i) {
    if (c[i] == 0) continue;
    if (n > 0 && c[i] == s[n-1].v)
      ++s[n-1].c;
    else {
      s[n].c = 1;
      s[n++].v =  c[i];
    }
  }
  return n;
}
int pred(const State& t) {
  int i, sum = 0;
  for (i = 0; i < t.n; ++i)
    sum += t.s[i].c;
  return t.d + (sum + 1)/2;
}
map<State, int> H;
int go(queue<State>& Q, const State& s, const State& s0) {
  int i, j, k;
/*  for (i = 0; i < s.n; ++i)
    printf("%d: %d\t", s.s[i].v, s.s[i].c);
  puts("");*/
  State t;
  for (i = 0; s.s[i].v < 0; ++i)
    for (j = s.n-1; s.s[j].v > 0; --j) {
      t = s;
      ++t.d;
      k = t.s[i].v + t.s[j].v;
      t.rm(i);
      t.rm(j);
      if (k != 0)t.ins(k);
      if (t.n == 0) return t.d;
      if (H.count(t)) continue;
      H[t] = t.d;
      if (pred(t) <= 20)
        Q.push(t);
      if ((t ^= s0) && H.count(t))
        return t.d + H[t];
    }
  return -1;
}
main() {
  int i, j, n, T, C = 1;
  scanf("%d", &T);
  while (T--) {
    for (i = 0; i < M; ++i) Count[i] = 0;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d", &j);
      go(j);
    }
    for (i = 0; i < M; ++i)
      Count[i] *= -1;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d", &j);
      go(j);
    }
    for (i = j = 0; i < M; ++i)
      j += Count[i];
    if (j != 0) {
      printf("Case %d: -1\n", C++);
      continue;
    }
    State start, t;
    start.d = 0;
    start.n = go(start.s, Count);
    queue<State> Q[2];
    Q[0].push(start);
    H.clear();
    for (i = 0; i < 10; ++i) {
      while (!Q[i%2].empty()) {
        t = Q[i%2].front();
        Q[i%2].pop();
        j = go(Q[1-i%2], t, start);
        if (j >= 0) break;
      }
      if (j >= 0) break;
    }
    printf("Case %d: %d\n", C++, j);
  }
}
