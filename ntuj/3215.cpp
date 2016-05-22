#include <stdio.h>

int dp[10005];
int child[10005][10];
int nc[10005];
int pos[10005];
char a[10005];
int st[10005], top=0;

void dfs(int x)
{
  if(a[x]=='a')
    printf("a");
  else {
    for(int i=0;i<nc[x];i++){
      dfs(child[x][(pos[x]+i)%nc[x]]);
    }
    printf("%d", nc[x]);
  }
}

int main(void)
{
  int i, j, k;
  while(scanf("%s", a)!=EOF)
  {
    top = 0;
    for(i=0;a[i];i++){
      if(a[i]=='a'){
        nc[i] = 0;
        pos[i] = 0;
        dp[i] = 1;
        st[top++] = i;
      }else{
        nc[i] = a[i] - '0';
        for(j=0;j<nc[i];j++){
          child[i][nc[i]-1-j] = st[--top];
        }
        st[top++] = i;
        dp[i] = 1000000;
        for(j=0;j<nc[i];j++){
          int s=0;
          for(k=0;k<nc[i];k++){
            if(s < dp[child[i][(j+k)%nc[i]]]+k)
              s = dp[child[i][(j+k)%nc[i]]]+k;
          }
          if(s < dp[i]){
            dp[i] = s;
            pos[i] = j;
          }
        }
      }
      //printf("dp[%d]=%d, pos=%d, nc=%d\n", i, dp[i], pos[i], nc[i]);
    }
    printf("%d\n", dp[i-1]);
    dfs(i-1);
    printf("\n");
  }
  return 0;
}
