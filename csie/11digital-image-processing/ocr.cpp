#include"io.h"
#include<queue>
#include<vector>
#include<string>
using namespace std;
const int dH = 256, dW = 256, mH = 1024, mW = 1024;
unsigned char data[dH][dW], s[dH][dW], map[mH][mW];
struct pt {
  int x, y;
};
int H, W;
inline int abs(int a) {return a<0?-a:a;}

void fix(vector<pt>& s) {
  int i, mx = s[0].x, my = s[0].y;
  for (i = 0; i < s.size(); ++i) {
    if (s[i].x < mx) mx = s[i].x;
    if (s[i].y < my) my = s[i].y;
  }
  for (i = 0; i < s.size(); ++i) {
    s[i].x -= mx - 1;
    s[i].y -= my - 1;
  }
}
vector<pt> tmp;
vector<vector<pt> > p;
void Init() {
  freopen("sample.raw", "r", stdin);
  LoadImage(dH*dW, data);
  int i, j, k, l, sum, x, y;
  for (i = 0; i < dH; ++i)
    for (j = 0; j < dW; ++j)
        map[i][j] = (data[i][j] < 128);
  for (i = 0; i < H; i = j) {
    for (j = i; j < H; ++j) {
      for (l = sum = 0; l < W; ++l)
        sum += map[j][l];
      if (sum < 1) {++j; break;}
    }
    if (j <= i + 1) continue;
    for (k = 0; k < W; ++k) {
      tmp.clear();
      for (; k < W; ++k) {
        for (sum = 0, l = i; l < j; ++l)
          if (map[l][k]) {
            tmp.push_back((pt){l, k});
            ++sum;
          }
        if (sum < 1) break;
      }
      if (tmp.size() > 0) {
        fix(tmp);
        p.push_back(tmp);
      }
    }
  }
}

void draw(const vector<pt>& s, int h, int w) {
  int i, j;
  for (i = 0; i < h; ++i)
    for (j = 0; j < w; ++j)
      map[i][j] = 0;
  for (i = 0; i < s.size(); ++i)
    map[s[i].x][s[i].y] = 1;
}

void zoom(vector<pt>& s, int x0, int y0, int x1, int y1) {
  draw(s, x0, y0);
  s.clear();
  int i, j;
  for (i = 0; i < x1; ++i)
    for (j = 0; j < y1; ++j)
      if (map[i*x0/x1][j*y0/y1])
        s.push_back((pt){i*x0/x1,j*y0/y1});
}

const int dx[] = {1, 0, -1, 0, -1, -1, 1, 1}, dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int lake_fill(int x, int y, int h, int w) {
  if (x < 0 || x >= h || y < 0 || y >= w) return 0;
  if (map[x][y]) return 1;
  map[x][y] = 1;
  int i, k, l = 1;
  for (i = 0; i < 4; ++i) {
    k = lake_fill(x+dx[i], y+dy[i], h, w);
    if (k <= 0 || l <= 0) l = 0;
    else l += k;
  }
  return l;
}

int lake(const vector<pt>& s, int h, int w) {
  int i, j, sum = 0;
  draw(s, h, w);
  for (i = 0; i < h; ++i)
    for (j = 0; j < w; ++j)
      if (map[i][j] == 0)
        sum += (lake_fill(i, j, h, w) > 5);
  return sum;
}

void conn_fill(int x, int y, int h, int w) {
  if (x < 0 || x >= h || y < 0 || y >= w) return;
  if (!map[x][y]) return;
  map[x][y] = 0;
  int i, k, l = 1;
  for (i = 0; i < 8; ++i)
    conn_fill(x+dx[i], y+dy[i], h, w);
}

int conn(const vector<pt>& s, int h, int w) {
  int i, j, sum = 0;
  draw(s, h, w);
  for (i = 0; i < h; ++i)
    for (j = 0; j < w; ++j)
      if (map[i][j] == 1)
        ++sum, conn_fill(i, j, h, w);
  return sum;
}

int buc(const vector<pt>& s, const vector<pt>& p, int mx, int my) {
  const int L = 3;
  int i, j, sum = 0, count[L][L];
  for (i = 0; i < L; ++i)
    for (j = 0; j < L; ++j)
      count[i][j] = 0;
  for (i = 0; i < s.size(); ++i)
    ++count[s[i].x*L/mx][s[i].y*L/my];
  for (i = 0; i < p.size(); ++i)
    --count[p[i].x*L/mx][p[i].y*L/my];
  for (i = sum = 0; i < L; ++i)
    for (j = 0; j < L; ++j)
      sum += abs(count[i][j]);
  return sum;
}

int hbuc(const vector<pt>& s, const vector<pt>& p, int mx, int my) {
  const int L = 3;
  int i, j, sum = 0, count[L];
  for (i = 0; i < L; ++i)
    count[i] = 0;
  for (i = 0; i < s.size(); ++i)
    ++count[s[i].x*L/mx];
  for (i = 0; i < p.size(); ++i)
    --count[p[i].x*L/mx];
  for (i = sum = 0; i < L; ++i)
    sum += abs(count[i]);
  return sum;
}

int vbuc(const vector<pt>& s, const vector<pt>& p, int mx, int my) {
  const int L = 3;
  int i, j, sum = 0, count[L];
  for (i = 0; i < L; ++i)
    count[i] = 0;
  for (i = 0; i < s.size(); ++i)
    ++count[s[i].y*L/my];
  for (i = 0; i < p.size(); ++i)
    --count[p[i].y*L/my];
  for (i = sum = 0; i < L; ++i)
    sum += abs(count[i]);
  return sum;
}

int bal(const vector<pt>& s, const vector<pt>& p, int h, int w) {
  int i, j, k, sum = 0;
  for (i = j = 0; i < s.size(); ++i) {
    if (s[i].x < h/2) --j;
    else ++j;
  }
  for (i = k = 0; i < p.size(); ++i) {
    if (p[i].x < h/2) --k;
    else ++k;
  }
  sum += abs(j-k);
  for (i = j = 0; i < s.size(); ++i) {
    if (s[i].y < w/2) --j;
    else ++j;
  }
  for (i = k = 0; i < p.size(); ++i) {
    if (p[i].y < w/2) --k;
    else ++k;
  }
  sum += abs(j-k);  
  for (i = j = 0; i < s.size(); ++i) {
    if (s[i].x+s[i].y < (h+w)/2) --j;
    else ++j;
  }
  for (i = k = 0; i < p.size(); ++i) {
    if (w+p[i].x-s[i].y < (h+w)/2) --k;
    else ++k;
  }
  sum += abs(j-k);
  Message("%d ", sum);
  return sum;
}

int vline(const vector<pt>& s, const vector<pt>& p, int h, int w) {
  const int L = 5;
  int i, j, k, c0[L], c1[L], sum = 0;
  for (i = 0; i < L; ++i)
    c0[i] = c1[i] = 0;
  draw(s, h, w);
  for (i = 0; i + 2 < w; ++i) {
    for (k = sum = 0; k < 2 && i+k < w; ++k)
      for (j = 0; j < h; ++j)
        sum += map[j][i+k];
    if (sum < h+h/2) continue;
    c1[i*L/w] = 1;
  }
  draw(p, h, w);
  for (i = 0; i + 2 < w; ++i) {
    for (k = sum = 0; k < 2 && i+k < w; ++k)
      for (j = 0; j < h; ++j)
        sum += map[j][i+k];
    if (sum < h+h/2) continue;
    c1[i*L/w] = 1;
  }
  for (i = sum = 0; i < L; ++i)
    sum += abs(c0[i] - c1[i]);
  return sum;
}
int hline(const vector<pt>& s, const vector<pt>& p, int h, int w) {
  const int L = 5;
  int i, j, k, c0[L], c1[L], sum = 0;
  for (i = 0; i < L; ++i)
    c0[i] = c1[i] = 0;
  draw(s, h, w);
  for (i = 0; i + 2 < h; ++i) {
    for (k = sum = 0; k < 2 && i+k < h; ++k)
      for (j = 0; j < w; ++j)
        sum += map[i+k][j];
    if (sum < w+w/2) continue;
    c1[i*L/h] = 1;
  }
  draw(p, h, w);
  for (i = 0; i + 2 < h; ++i) {
    for (k = sum = 0; k < 2 && i+k < h; ++k)
      for (j = 0; j < w; ++j)
        sum += map[i+k][j];
    if (sum < w+w/2) continue;
    c1[i*L/h] = 1;
  }
  for (i = sum = 0; i < L; ++i)
    sum += abs(c0[i] - c1[i]);
  return sum;
}
inline int perimeter(const vector<pt>& s, int h, int w) {
  draw(s, h, w);
  int i, j, k, nx, ny, sum = 0;
  for (i = 0; i < h; ++i)
    for (j = 0; j < w; ++j) {
      if (!map[i][j]) continue;
      for (k = 0; k < 4; ++k) {
        nx = i + dx[k], ny = j + dy[k];
        if (nx < 0 || nx >= h || ny < 0 || ny >= w || !map[nx][ny])
          ++sum;
      }
    }
  return sum;
}
int d[mH][mW];
int dis(const vector<pt>& s, const vector<pt>& p, int h, int w) {
  draw(p, h, w);
  queue<pt> Q;
  int i, j, k, sum, nx, ny;
  for (i = 0; i < h; ++i)
    for (j = 0; j < w; ++j)
      if (map[i][j]) {
        Q.push((pt){i, j});
        d[i][j] = 0;
      }
      else d[i][j] = h+w;
  while (!Q.empty()) {
    j = Q.front().x, k = Q.front().y;
    Q.pop();
    for (i = 0; i < 4; ++i) {
      nx = j + dx[i], ny = j + dy[i];
      if (nx < 0 || nx >= h || ny < 0 || ny >= w || d[j][k] + 1 > d[nx][ny])
        continue;
      d[nx][ny] = d[j][k] + 1;
      Q.push((pt){nx, ny});
    }
  }
  for (i = sum = 0; i < s.size(); ++i)
    sum += d[s[i].x][s[i].y];
  return sum;
}
int Match(const vector<pt>& t0, const vector<pt>& p0) {
  int i, j, k, sum = 0, mx, my, mx0, my0, mx1, my1;
  mx0 = t0[0].x;
  my0 = t0[0].y;
  mx1 = p0[0].x;
  my1 = p0[0].y;
  for (i = 0; i < t0.size(); ++i) {
    if (t0[i].x > mx0) mx0 = t0[i].x;
    if (t0[i].y > my0) my0 = t0[i].y;
  }
  for (i = 0; i < p0.size(); ++i) {
    if (p0[i].x > mx1) mx1 = p0[i].x;
    if (p0[i].y > my1) my1 = p0[i].y;
  }
  //Message("%d %d %d %d\n", mx0, my0, mx1, my1);
  mx = mx0 > mx1? mx0:mx1;
  my = my0 > my1? my0:my1;
  vector<pt> t = t0, p = p0;
  if (mx > mx0 || my > my0)
    zoom(t, mx0, my0, mx, my);
  if (mx > mx1 || my > my1)
    zoom(p, mx1, my1, mx, my);
  ++mx, ++my;
  const int w[] = {32768, 16, 2, 64, 1, 16};
  sum += w[0] * abs(lake(t, mx, my) - lake(p, mx, my));
  sum += w[0] * abs(conn(t, mx, my) - conn(p, mx, my));
  sum += w[1] * buc(t, p, mx, my);
  sum += w[1] * hbuc(t, p, mx, my);
  sum += w[1] * vbuc(t, p, mx, my);
  sum += w[2] * abs(perimeter(t, mx, my) - perimeter(p, mx, my));
  sum += w[3] * hline(t, p, mx, my);
  sum += w[3] * vline(t, p, mx, my);
  sum += w[5] * bal(t, p, mx, my);
  j = dis(t, p, mx, my);
  k = dis(p, t, mx, my);
  if (k < j) j = k;
//  sum += j;
  Message("\n");
  return sum;
}

void Split() {
  int a, i, j, k, l, sum, d[22], bl[22];
  vector<vector<pt> > t;
  for (i = 0; i < H; ++i)
    for (j = 0; j < W; ++j)
      map[i][j] = (s[i][j] < 128);
  for (i = 0; i < H; i = j) {
    for (j = i; j < H; ++j) {
      for (l = sum = 0; l < W; ++l)
        sum += map[j][l];
      if (sum < 1) {++j; break;}
    }
    if (j <= i + 1) continue;
    for (k = 0; k < W; ++k) {
      tmp.clear();
      for (; k < W; ++k) {
        for (sum = 0, l = i; l < j; ++l)
          if (map[l][k]) {
            tmp.push_back((pt){l, k});
            ++sum;
          }
        if (sum < 1) break;
      }
      if (tmp.size() > 0) {
        fix(tmp);        
        t.push_back(tmp);
        bl[t.size()] = 0;
      }
    }
    bl[t.size()] = 1;
  }

  const char symbol[] = "abcdemnopqrstuv!@#$%";
  string res = "";
  for (i = 0; i < t.size(); ++i) {
    Message("Char %d\n", i);
    for (j = a = 0; j < 20; ++j) {
      d[j] = Match(t[i], p[j]);
      if (d[j] < d[a]) a = j;
    }
    Message("\n");
    if (bl[i] && res.length() > 0) res.push_back('\n');
    res.push_back(symbol[a]);    
  }
  printf("%s\n", res.c_str());
}

int main(int argc, char **argv) {
  int i, j;
  H = W = 256;
  if (argc > 2) {
    sscanf(argv[2], "%d", &H);
    sscanf(argv[3], "%d", &W);
  }  
  LoadImage(H*W, s);
  Init();
  Split();
}

