#include<map>
#include<list>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 50005;
int num[N*4], tmp[N*4], label[N*4], from[N], to[N], arg[N];
char type[N][3];
void print(list<int>& Q) {
  list<int>::iterator i;
  int j = 0;
  for (i = Q.begin(); i != Q.end(); ++i)
    printf("%d,%d[%d] ", j++, label[*i], num[*i]);
  puts("");
}
void Move(list<int>& Q, vector<list<int>::iterator>& L, int a, int b) {
  list<int>::iterator p = L[a];
  --p;
  num[*p] += num[a] - 1;
  num[a] = 1;
  int tmp = *L[a];
  Q.erase(L[a]);
  L[a] = Q.insert(L[b], tmp);
}
int Find(int pos, int n) {
  int i, j, k, a;
  for (i = 1, j = n - 1; i <= j; ) {
    k = (i + j)/2;
    if (num[tmp[k]] <= pos) i = k + 1;
    else a = k, j = k - 1;
  }
  if (pos == num[tmp[a-1]]) return label[tmp[a]];
  pos -= a;
  for (i = 0, j = n - 1; i <= j; ) {
    k = (i + j)/2;
    if (pos+k > label[k]) a = k, i = k + 1;
    else j = k-1;
  }
  return pos+a;
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j = 0, k, n, m;
    tmp[j++] = 0;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d %d", from+i, to+i);
      tmp[j++] = from[i];
      tmp[j++] = to[i];
    }
    scanf("%d", &m);
    for (i = 0; i < m; ++i) {
      scanf("%s %d", type+i, arg+i);
      tmp[j++] = arg[i];
    }
    sort(tmp, tmp + j);
    map<int, int> H;
    list<int> Q;
    vector<list<int>::iterator> L;
    for (i = 0; i < j; ++i)
      if (0 == H.count(tmp[i])) {
        k = H.size();
        H[tmp[i]] = k;
        tmp[k] = tmp[i];
        Q.push_back(k);
        if (L.size() > 0)
          num[*L.back()] = tmp[i] - tmp[*L.back()];
        L.push_back(Q.end());
        --L.back();
      }
    num[*L.back()] = 1;
    for (i = 0; i < n; ++i)
      Move(Q, L, H[from[i]], H[to[i]]);
    copy(tmp, tmp + j, label);
    copy(Q.begin(), Q.end(), tmp);
    int qn = Q.size();
    for (i = 1; i < qn; ++i)
      num[tmp[i]] += num[tmp[i-1]];
    for (i = 0; i < m; ++i) {
      if (type[i][0] == 'P') {
        list<int>::iterator p = L[H[arg[i]]];
        printf("%d\n", num[*--p]);
      }
      else
        printf("%d\n", Find(arg[i], qn));
    }
  }
}
