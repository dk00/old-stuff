#include<cstdio>
const int N = 999;
char s[N][N], next[N][N];
int fix(int i, int j) {
  if ((i+j) % 2) {
    if (s[i][j] == '<' && s[i+1][j] == '<' && 
        s[i][j+1] =='>' && s[i+1][j+1] =='>') {
      s[i][j] = s[i][j+1] = '^';
      s[i+1][j] = s[i+1][j+1] = 'v';
      return 1;
    }
  }
  else {
    if (s[i][j] == '^' && s[i+1][j] == 'v' && 
        s[i][j+1] =='^' && s[i+1][j+1] =='v') {
      s[i][j] = s[i+1][j] = '<';
      s[i][j+1] = s[i+1][j+1] = '>';
      return 1;
    }    
  }
  return 0;
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, n;
    scanf("%d", &n);
    gets(s[0]);
    for (i = 0; i < n; ++i) {
      gets(s[i]);
      for (j = 0; s[i][j]; ++j)
        next[i][j] = 1;
    }
    for (j = 0; j < N; ++j)
      s[n][j] = 0;
    k = 1;
    int error = 0;
    while (k > 0) {
      k = 0;
      for (i = 0; i < n; ++i)
        for (j = 0; s[i][j]; ++j) {
          if (s[i][j] == '<' && s[i][j+1] !='>') error = 1;
          if (j > 0 && s[i][j-1] != '<' && s[i][j] =='>') error = 1;
          if (s[i][j] =='^' && s[i+1][j] !='v') error = 1;
          if (i > 0 && s[i-1][j] !='^' && s[i][j] =='v') error = 1;
          if (next[i][j] && fix(i, j)) {
            next[i+1][j] = next[i][j+1] = 1;
            if (i > 0) next[i-1][j] = 1;
            if (j > 0) next[i][j-1] = 1;
            ++k;
          }
        }
    }
    if (error) {
      puts("Run away little girl. Run Away!\n");
      continue;
    }
    for (i = 0; i < n; ++i) {
      for (j = 0; s[i][j]; ++j);
      j--;
      while(j >= 0 && s[i][j] == ' ')
        s[i][j--] = 0;
      puts(s[i]);
    }
    puts("");
  }
}
