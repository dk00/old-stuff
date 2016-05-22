#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;

map<pair<int, int>, int> dp[4];

char a[15][105];
char s[1000];
int nid;

int dfs(int p, int L, int R, int x)
{
  if(dp[x].find(pair<int, int>(L, R)) != dp[x].end())
    return dp[x][pair<int, int>(L, R)];
  if(s[L] != '('){
    int nd = 0;
    sscanf(s+L, "%d", &nd);
    if(a[nd][p] != x) return 100000;
    return 0;
  }else{
    int mk, csv = 0;
    for(mk=L+1;mk<=R;mk++){
      if(s[mk]=='(') ++csv;
      else if(s[mk]==')') --csv;
      else if(s[mk] == ',' && csv==0)
        break;
    }
    int i, j, mc = 100000;
    for(i=0;i<4;i++)
      for(j=0;j<4;j++){
        int c = dfs(p, L+1, mk-1, i) + dfs(p, mk+1, R-1, j)
          + (i!=x) + (j!=x);
        if(c < mc) mc = c;
      }
    //printf("p=%d, L=%d, R=%d, x=%d, mc=%d\n", p, L, R, x, mc);
    dp[x][pair<int, int>(L, R)] = mc;
    return mc;
  }
}

int main(void)
{
  int T, i, j;
  scanf("%d", &T);
  while(T--){
    int n, L;
    scanf("%d%d", &n, &L);
    for(i=0;i<n;i++){
      scanf("%s", a[i]);
    }
    for(i=0;i<n;i++){
      for(j=0;j<L;j++)
        if(a[i][j]=='A') a[i][j]=0;
        else if(a[i][j]=='C') a[i][j]=1;
        else if(a[i][j]=='T') a[i][j]=2;
        else a[i][j]=3;
    }

    int cst = 0;
    scanf("%s", s);
    int k;
    for(k=0;s[k];k++);
    for(i=0;i<L;i++){
      for(j=0;j<4;j++)
        dp[j].clear();
      int mn=1000000;
      for(j=0;j<4;j++){
        int t=dfs(i, 0, k-1, j);
        if(t < mn) mn = t;
      }
      cst += mn;
    }
    printf("%d\n", cst);
  }
  return 0;
}
