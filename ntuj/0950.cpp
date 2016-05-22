#include<stack>
#include<cstdio>
using namespace std;
const int N = 505, M = 6, inf = 2000000000;
int n, m, mul[M], h[M], w[M], p[N], s[N][N], t[N][N], t0[N][N];
inline void Sum(int t[N][N], int h, int w, int mul) {
  int i, j;
  for (i = 0; i+h-1 < n; ++i)
    for (j = 0; j+w-1 < m; ++j)
      t[i][j] += mul * (s[i+h-1][j+w-1] - (i?s[i-1][j+w-1]:0) 
        - (j?s[i+h-1][j-1]:0) + ((i && j)?s[i-1][j-1]:0));
}
void go(int t[N][N], int h, int w, int h0, int w0) {
  stack<int> st;
  int i, j, k;
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
      t0[i][j] = -inf;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j) {
      while (!st.empty() && t[i][j] > t[i][st.top()]) {
        p[st.top()] = j;
        st.pop();
      }
      st.push(j);
    }
    while (!st.empty()) {
      p[st.top()] = st.top();
      st.pop();
    }
    for (j = k = 0; j+w-1 < m; ++j) {
      if (k < j) k = j;
      while (p[k] > k && p[k]+w0-1 < j+w) k = p[k];
      t0[i][j] = t[i][k];
    }
  }
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
      t[i][j] = -inf;
  for (j = 0; j < m; ++j) {
    for (i = 0; i < n; ++i) {
      while (!st.empty() && t0[i][j] > t0[st.top()][j]) {
        p[st.top()] = i;
        st.pop();
      }
      st.push(i);
    }
    while (!st.empty()) {
      p[st.top()] = st.top();
      st.pop();
    }
    for (i = k = 0; i+h-1 < n; ++i) {
      if (k <= i) k = i;
      while (p[k] > k && p[k]+h0-1 < i+h) k = p[k];
      t[i][j] = t0[k][j];
    }
  }
}

main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, m0;
    scanf("%d %d %d", &n, &m, &k);
    h[0] = n, w[0] = m;
    for (++k, i = 1; i < k; ++i)
      scanf("%d", h+i);
    for (i = 1; i < k; ++i)
      scanf("%d", w+i);    
    scanf("%d", mul);
    for (i = 1; i < k; ++i)
      scanf("%d", mul+i);
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j) {
        scanf("%d", &s[i][j]);
        if (j) s[i][j] += s[i][j-1];
        t[i][j] = 0, t0[i][j] = -inf;
      }
    for (j = 0; j < m; ++j)
      for (i = 1; i < n; ++i)
        s[i][j] += s[i-1][j];
    for (i = k - 1; i > 0; --i) {
      Sum(t, h[i], w[i], mul[i]-mul[i-1]);
      go(t, h[i-1], w[i-1], h[i], w[i]);
    }
    Sum(t, h[i], w[i], mul[0]);
    k = t[0][0];
    for (i = 0; i+h[0]-1 < n; ++i)
      for (j = 0; j+w[0]-1 < m; ++j)
        if (t[i][j] > k) k =  t[i][j];
    printf("%d\n", k);
  }
}
