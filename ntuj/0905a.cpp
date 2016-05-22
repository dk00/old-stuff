#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int D = 16, N = 1<<D;
struct pt {
  int x, y, z;
}s[N];
int Max, s0[N], s1[N], s2[N];
void Discrete(map<int, int>& h, int s[], int n) {
  sort(s, s+n);
  int i, j = n;
  for (i = n = 1; i < j; ++i)
    if (s[i] != s[i-1]) s[n++] = s[i];
  for (i = 0; i < n; ++i){
    if (i && s[i] == s[i-1]) continue;
    h[s[i]] = i;
  }
  for (i = 1; i < n; i *= 2);
  i/=2;
  if (i > Max) Max = i;
}
int gen0(int x, int s[]) {
  int i, n = 1;
  s[0] = x;
  if (x < 0) return 0;
  for (i = 1; i <= Max; i *= 2)
    if (i&~x) s[n++] = x += i;
  return n;
}
int gen(int x, int s[]) {
  if (x < 0) return 0;
  int i, n = 1;  
  s[0] = x;
  for (i = 1; i <= x; i *= 2)
    if (i&~x) s[n++] = x -= i;
  return n;
}
void Add(map<long long, int>& H, int n0, int n1, int n2,
   int s0[], int s1[], int s2[]) {
  int i, j, k;
  for (i = 0; i < n0; ++i)
    for (j = 0; j < n1; ++j)
      for (k = 0; k < n2; ++k) {
        long long key = s0[i];
        key = (key << 16) + s1[j];
        key = (key << 16) + s2[k];
        ++H[key];
      }
}
long long Count(map<long long, int>& H, int n0, int n1, int n2,
   int s0[], int s1[], int s2[]) {
  int i, j, k;
  long long sum = 0;
  for (i = 0; i < n0; ++i)
    for (j = 0; j < n1; ++j)
      for (k = 0; k < n2; ++k) {
        long long key = s0[i];
        key = (key << 16) + s1[j];
        key = (key << 16) + s2[k];        
        sum += H[key];
      }
  return sum;  
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, n, n0, n1, n2;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d %d %d", &s[i].x, &s[i].y, &s[i].z);
      s0[i] = s[i].x;
      s1[i] = s[i].y;
      s2[i] = s[i].z;
    }
    map<int, int> h0, h1, h2;
    Max = 0;
    Discrete(h0, s0, n);
    Discrete(h1, s1, n);
    Discrete(h2, s2, n);
    map<long long, int> H;
    for (i = 0; i < n; ++i) {
      s[i].x = h0[s[i].x];
      s[i].y = h1[s[i].y];
      s[i].z = h2[s[i].z];
      n0 = gen0(s[i].x, s0);
      n1 = gen0(s[i].y, s1);
      n2 = gen0(s[i].z, s2);
      Add(H, n0, n1, n2, s0, s1, s2);
    }
    long long sum = 0;
    for (i = 0; i < n; ++i) {
      n0 = gen(s[i].x - 1, s0);
      n1 = gen(s[i].y - 1, s1);
      n2 = gen(s[i].z - 1, s2);      
      sum += Count(H, n0, n1, n2, s0, s1, s2);
    }
    printf("%lld\n", sum);
  }
}
