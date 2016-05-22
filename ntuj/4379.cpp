#include<string>
#include<cstdio>
using namespace std;
char name_ch[256], tmp[999999];
main() {
  int i, j, k;
  for (i = 0; i < 26; ++i)
    name_ch[i + 'a'] = name_ch[i + 'A'] = 1;
  while (gets(tmp)) {
    for (i = 0; tmp[i] != ' '; ++i);
    tmp[i] = 0;
    string type0 = tmp;
    for (++i; tmp[i]; i = j + 1) {
      if (tmp[i] == ' ') ++i;
      for (j = i; tmp[j] != ',' && tmp[j] !=';'; ++j);
      string type1;
      for (k = j - 1; !name_ch[tmp[k]]; --k) {
        if (tmp[k] == ']') continue;
        type1.push_back(tmp[k]);
        if (tmp[k] == '[') type1.push_back(']');
      }
      tmp[k+1] = 0;
      printf("%s%s %s;\n", type0.c_str(), type1.c_str(), tmp+i);
    }
  }
}
