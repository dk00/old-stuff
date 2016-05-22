#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 100001;
char tmp[N], tmp1[N];
inline void rep(char c, int n) {
  while (n--) putchar(c);
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int m, len, padding = 1;
    string username, title = "Welcome", ok_msg = "OK";
    scanf("%d", &m);
    while (m--) {
      
      scanf(" %[USERNAMETILPDGOK_] = ", tmp);
      if (!strcmp(tmp, "PADDING")) {
        scanf("%d", &padding);
        continue;
      }
      scanf("%[^\r\n]", tmp1);
      if (!strcmp(tmp, "USERNAME"))
        username = tmp1;
      if (!strcmp(tmp, "TITLE"))
        title = tmp1;
      if (!strcmp(tmp, "OK_MSG"))
        ok_msg = tmp1;
    }
    len = max(username.length() + padding*2 + 1,
        max(title.length() + 2, ok_msg.length() + 4));
    len = max(21 + padding*2, len);
    printf("+");
    rep('-', len);
    printf("+\n|%s", title.c_str());
    rep(' ', len - title.length() - 2);
    printf(" X|\n+");
    rep('-', len);
    printf("+\n|");
    rep(' ', len);
    printf("|\n|");
    rep(' ', padding);
    printf("Welcome to NTUJ 2010,");
    rep(' ', len - padding - 21);
    printf("|\n|");
    rep(' ', padding);
    printf("%s.", username.c_str());
    rep(' ', len - padding - username.length() - 1);
    printf("|\n|");
    rep(' ', len);
    printf("|\n|");
    rep(' ', (len - 4 - ok_msg.length()) / 2);
    printf("< %s >", ok_msg.c_str());
    rep(' ', (len - 4 - ok_msg.length() + 1) / 2);
    printf("|\n+");
    rep('-', len);
    printf("+\n");    
  }
}
