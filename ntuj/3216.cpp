#include<map>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 20002;
vector<string> s[N];
int p[N];
char tmp[N], word[N];
void read(string& s) {
  gets(tmp);
  for (i = 0; 
}
main() {
  int n, m;
  scanf("%d", &n);
  while (gets(s[0])) {
    map<string, vector<int> > H;
    if (!tmp[0]) break;
    for (n = m = 0; ; ++n) {
      read(s[n]);
      if (n > 0 && s[n] == "" && s[n-1] == "") {
        --n;
        break;
      }
      if (s[n] == "")p[m++] = n;
    }
  }
}
