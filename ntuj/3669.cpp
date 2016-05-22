#include <stdio.h>
#include <string.h>

int main(void)
{
  char a[10005];
  int T;
  scanf("%d", &T);
  int c[10005], i, j, k, n;
  while(T--){
    int b[10005]={0};
    scanf("%d", &n);
    for(i=0;i<n;i++){
      scanf("%d", &c[i]);
    }
    scanf("%s", a+1);
    int m = 0;
    for(m=1;a[m];m++);
    --m;
    b[m] = 1;
    b[0] = 1;
    int cnt=0;
    for(i=0;i<n;i++){
      int s[26]={0};
      for(j=c[i];b[j]==0;j--)
        if(s[a[j]-'a'] == 0)
          s[a[j]-'a']=1, ++cnt;
      for(k=c[i]+1;b[k-1]==0;k++)
        if(s[a[k]-'a'] == 0)
           s[a[k]-'a']=2, ++cnt;
        else if(s[a[k]-'a'] == 1)
          s[a[k]-'a'] = 2, --cnt;
      b[c[i]] = 1;
    }
    printf("%d\n", cnt);
  }
  return 0;
}
