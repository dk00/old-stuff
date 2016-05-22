#include <stdio.h>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

int a[1005][4];
int siz[1005];
int n;
int r[4];

class Event {
  public:
    int t, L, R, v;
    Event(int tt=0, int ll=0, int rr=0, int vv=0) {
      t = tt; L = ll; R = rr; v=vv;
    }
    bool operator<(const Event &e) const {
      return t < e.t || t==e.t && v < e.v;
    }
} e[2005];
class Segment {
  public:
    int maxvalue, maxpos, value;
    Segment(int m=0,int p=0, int v=0) {
      maxvalue = m; maxpos = p; value = v;
    }
};
Segment seg[100005];
int ne;
int yy[50005];

inline void init(int x, int L, int R) {
  if(L==R) {
    seg[x].maxvalue = 0;
    seg[x].maxpos = L;
    seg[x].value = 0;
  } else {
    seg[x].maxvalue = 0;
    seg[x].maxpos = L;
    seg[x].value = 0;
    init(x*2, L, (L+R)/2);
    init(x*2+1, (L+R)/2+1, R);
  }
}

inline void combine(int x) {
  int y = x*2, z = x*2+1;
  if(seg[y].maxvalue >= seg[z].maxvalue) {
    seg[x].maxvalue = seg[y].maxvalue + seg[x].value;
    seg[x].maxpos = seg[y].maxpos;
  } else {
    seg[x].maxvalue = seg[z].maxvalue + seg[x].value;
    seg[x].maxpos = seg[z].maxpos;
  }
}
int cnt=0;
inline void update(int x, int L, int R, int vL, int vR, int v) {

  ++cnt;
  if(vL <= L && vR >= R) {
    seg[x].value += v;
    seg[x].maxvalue += v;
  } else {
    int M = (L+R)/2;
    if(vL <= M) update(x*2, L, M, vL, vR, v);
    if(vR > M) update(x*2+1, M+1, R, vL, vR, v);
    combine(x);
  }
}
int ans=0;
int go(int side) {
  int i, d=0;
  ne = 0;
  set<int> s;
  map<int, int> ymap;
  for(i=0;i<n;i++) {
    if(siz[i] >= side) {
      e[ne].t = a[i][0] - side + 1;
      e[ne].L = a[i][1] - side + 1;
      e[ne].R = a[i][3] - 1;
      s.insert(e[ne].L);
      s.insert(e[ne].R);
      e[ne++].v = 1;
      e[ne].t = a[i][2];
      e[ne].L = a[i][1] - side + 1;
      e[ne].R = a[i][3] - 1;
      s.insert(e[ne].L);
      s.insert(e[ne].R);
      e[ne++].v = -1;
      ++d;
    }
  }
  if(d<=ans) return -1;
  i=0;
  int len = s.size();
  for(set<int>::iterator it = s.begin(); it != s.end(); it++) {
    ymap[*it] = ++i;
    yy[i] = *it;
  }
  sort(e, e+ne);
  init(1, 1, len);
  int mx=0;
  for(i=0;i<ne;i++) {
    //printf("t=%d %d %d %d\n", e[i].t, e[i].L, e[i].R, e[i].v);

    update(1, 1, len, ymap[e[i].L], ymap[e[i].R], e[i].v);
    if(seg[1].maxvalue > mx) {
      mx = seg[1].maxvalue;
      r[0] = e[i].t;
      r[1] = yy[seg[1].maxpos];
      r[2] = r[0]+side;
      r[3] = r[1]+side;
    }
  }
  return mx;
}

int main(void)
{ 
  int i, j;
  while(scanf("%d", &n)!=EOF) {
    if(n==0) break;
    for(i=0;i<n;i++) {
      for(j=0;j<4;j++)
        scanf("%d", &a[i][j]);
      siz[i] = a[i][2]-a[i][0];
    }
    int mx=0, v;
    int p[4];
    set<int> usedsiz;
    ans = 0;
    for(i=0;i<n;i++) {
      if(usedsiz.count(siz[i])) continue;
      usedsiz.insert(siz[i]);
      v=go(siz[i]);
      if(v>mx){
        mx = v;
        ans = mx;
        for(j=0;j<4;j++)
          p[j] = r[j];
        //printf("ans=%d\n", ans);
        if(ans>=4) break;
      }
    }
    printf("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
  }
  return 0;
}
