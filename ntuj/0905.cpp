#include<set>
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int D = 16, N = 1<<D;
struct pt {
  int x, y, z;
  bool operator<(pt a) const {
    if (z != a.z) return z < a.z;
    if (y != a.y) return y < a.y;
    if (x != a.x) return x < a.x;
  }
}s[N];
struct node {
  unsigned num, lb, ub, val, count;
  node *l, *r;
  node() {
    l = r = NULL;
    num = 1;
  }
};
class Lazy {
public:
  void init(unsigned n) {
    ub = n
    root = NULL;
  }
  void insert(unsigned val, unsigned count = 1, node *&p = root, unsigned s = lb, unsigned t = ub) {
    if (p == NULL) {
      p = new node;
      p->count = count;
      p->lb = s;
      p->ub = t;
      p->val = val;
      return;
    }
    unsigned mid = (p->lb + p->ub)/2;
    if (val == p->val) {
      ++p->count;
      return;
    }
    if (abs(val - mid) < abs(p->val - mid)) {
      swap(val, p->val);
      swap(count, p->count);
    }
    if (val == mid) {
      printf("Error\n");
      scanf(" ");
    }
    if (val < mid) ++p->num, insert(val, p->l, s, mid-1);
    else insert(val, p->r, mid+1, t);
  }
  long long count_le(unsigned val, const node *p = root) {
    if (val < p->val)
      return count_le(val, p->l);
    return p->num + count(val, p->r);
        
  }
  ~Lazy() {
    Clean(root);
  }
private:
  int ub;
  void clean(node *p) {
    if (p != NULL) return;
    Clean(p->l);
    Clean(p->r);
    delete p;
  }
  node *root;
};
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
inline int gen0(int x, int s[]) {
  int i, n = 1;
  s[0] = x;
  if (x < 0) return 0;
  for (i = 1; i <= Max; i *= 2)
    if (i&~x) s[n++] = x += i;
  return n;
}
inline int gen(int x, int s[]) {
  if (x < 0) return 0;
  int i, n = 1;  
  s[0] = x;
  for (i = 1; i <= x; i *= 2)
    if (i&~x) s[n++] = x -= i;
  return n;
}
inline unsigned Key(unsigned a, unsigned b) {
  return (a << 16)|b;
}
inline void Add(int n0, int n1, int s0[], int s1[]) {
  int i, j;
  for (i = 0; i < n0; ++i)
    for (j = 0; j < n1; ++j){
        H[s0[i]].insert(s1[j]);
        //++test[Key(s0[i], s1[j])&65535];
      }
}
inline long long Count(multiset<unsigned>& H, int n0, int n1,int s0[], int s1[]) {
  int i, j;
  long long sum = 0;
  for (i = 0; i < n0; ++i)
    for (j = 0; j < n1; ++j) {
      sum += H[s0[i]].count_le(s1[j]);
      //sum += test[Key(s0[i], s1[j])&65535];
    }
  return sum;  
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, n, n0, n1;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d %d %d", &s[i].x, &s[i].y, &s[i].z);
      s0[i] = s[i].x;
      s1[i] = s[i].y;
    }
    sort(s, s+n);
    map<int, int> h0, h1;
    Max = 0;
    Discrete(h0, s0, n);
    Discrete(h1, s1, n);
    multiset<unsigned> H;
    long long sum = 0;
    for (j = 0; j < n; j = i) {
      for (i = j; i < n && s[i].z == s[j].z; ++i) {
        s[i].x = h0[s[i].x];
        s[i].y = h1[s[i].y];
        n0 = gen(s[i].x - 1, s0);
        n1 = gen(s[i].y - 1, s1);
        sum += Count(H, n0, n1, s0, s1);
      }
      for (i = j; i < n && s[i].z == s[j].z; ++i) {
        n0 = gen0(s[i].x, s0);
        n1 = gen0(s[i].y, s1);
        Add(H, n0, n1, s0, s1);
      }
    }
    printf("%lld\n", sum);
  }
}
