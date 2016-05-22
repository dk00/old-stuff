#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 105;
struct pt {
  int x, y, type;
  bool operator<(pt a) const{
    if (x != a.x) return x < a.x;
    return y < a.y;
  }
  pt operator-(pt a) {
    pt tmp = *this;
    tmp.x -= a.x;
    tmp.y -= a.y;
    return tmp;
  }
  int operator*(pt a) {
    return x*a.y - y*a.x;
  }
}O, nn, s[N*3];
bool cmp(pt a, pt b) {
  a = (a - O);
  b = (b - O);
  if (nn * a < 0 && b * nn < 0) return true;
  int tmp = a*b;  
  return  tmp < 0;
}
inline bool line(pt a, pt b, pt c) {
  return (a.x*b.y + b.x*c.y + c.x*a.y
    - a.y*b.x - b.y*c.x - c.y*a.x == 0)
  && abs(a.x-b.x) == abs(a.x-c.x) + abs(b.x-c.x)
  && abs(a.y-b.y) == abs(a.y-c.y) + abs(b.y-c.y);
}
inline int dis(pt a, pt b, pt c) {
  if (a < b) {
    pt tmp = a; a = b; b = tmp;
  }
  int v = (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
  if (v > 0) v = 1;
  else if (v < 0) v = -1;
  return v;
}

int main() {
  int i, j, k, n0, n1;
  nn.x = 1;
  nn.y = 0;
  while (scanf("%d %d", &n0, &n1) == 2 && n0 + n1) {
    for (i = 0; i < n0; ++i) {
      scanf("%d %d", &s[i].x, &s[i].y);
      s[i].type = 0;
    }
    for (i = n0; i < n0 + n1; ++i) {
      scanf("%d %d", &s[i].x, &s[i].y);
      s[i].type = 1;
    }
    for (i = 0; i < n0; ++i)
      for (j = i+1; j < n0; ++j)
        for (k = n0; k < n0 + n1; ++k)
          if (line(s[i], s[j], s[k]))
            goto end;
    for (i = n0; i < n0 + n1; ++i)
      for (j = i+1; j < n0 + n1; ++j)
        for (k = 0; k < n0; ++k)
          if (line(s[i], s[j], s[k]))
            goto end;
    int flag[2], tmp;
    for (i = 0; i < n0; ++i) {
      for (j = n0; j < n0 + n1; ++j) {
        flag[0] = flag[1] = 0;        
        for (k = 0; k < n0 + n1; ++k) {
          if (k == i || k == j) continue;
          tmp = dis(s[i], s[j], s[k]);
          if (flag[s[k].type]*tmp < 0)
            break;
          flag[s[k].type] = tmp;
        }
        if (k >= n0 + n1 && flag[0]*flag[1] <= 0)
          break;
      }
      if (j < n0 + n1) break;
    }
    if (i < n0) puts("YES");    
    else {
end:      
      puts("NO");
    }
  }
}
