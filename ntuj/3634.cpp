#include<map>
#include<stack>
#include<vector>
#include<string>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const string PUSH = "PUSH", DUP = "DUP", UNION = "UNION", 
      INTERSECT = "INTERSECT", ADD = "ADD";
int Size(const string& s) {
  if (s.size() < 3) return 0;
  return 1 + count(s.c_str(), s.c_str()+s.size(), ',');
}
char tmp[9999];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    unsigned i, m;    
    scanf("%u", &m);
    stack<vector<int> > S;
    while (m--) {
      char cmd[11], *p;
      vector<int> a, b, c;
      vector<string> s;
      scanf("%s", cmd);
      if (DUP == cmd) {
        S.push(S.top());
        goto End;
      }
      if (PUSH == cmd) {
        S.push("{}");
        goto End;
      }
      a = S.top();
      S.pop();
      b = S.top();
      S.pop();
      a.erase(0, 1);
      a.erase(a.size()-1, 1);
      strcpy(tmp, a.c_str());
      p = strtok(tmp, ",");      
      while (p != NULL) {
        s.push_back(p);
        p = strtok(NULL, ",");
      }      
      if (ADD == cmd) {
        s.push_back(b);
        sort(s.begin(), s.end());
        c = "{" + s[0];
        for (i = 1; i < s.size(); ++i)
          if (s[i] != s[i-1]) c += "," + s[i];
        S.push(c + "}");
        goto End;
      }
      b.erase(0, 1);
      b.erase(b.size()-1, 1);
      strcpy(tmp, b.c_str());
      tmp[b.size()] = 0;
      p = strtok(tmp, ",");
      while (p != NULL) {
        s.push_back(p);
        p = strtok(NULL, ",");
      }
      c = "{";
      sort(s.begin(), s.end());
      if (UNION == cmd) {
        c += s[0];
        for (i = 1; i < s.size(); ++i)
          if (s[i] != s[i-1]) c += "," + s[i];
      }
      if (INTERSECT == cmd)
        for (i = 0; i < s.size(); ++i)
          if (i + 1 < s.size() && s[i] == s[i+1])
            c += "," + s[i];
      S.push(c+"}");
End:  printf("%d\n", Size(S.top()));
    }
    puts("***");
  }
}
