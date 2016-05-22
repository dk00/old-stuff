#include <stdio.h>

char a[105];
int w = 'B' + 'W';
int mn, n;
void dfs(int pos, int lev){
  int i, j, k;
  if(lev >= mn) return;
  for(i=0;a[i] && a[i]!='B';i++);
  for(j=n-1;j>=0 && a[j]!='B';j--);
  for(k=i+1;k<j;k++)
    if(a[k]=='W')
      break;
  if(k>=j) {if(lev < mn) mn = lev; return ;}
  if(pos>0){
    a[pos] = a[pos-1];
    a[pos-1] = 'F';
    dfs(pos-1, lev+1);
    a[pos-1] = a[pos];
    a[pos] = 'F';
  }
  if(pos>1){
    a[pos] = w - a[pos-2];
    a[pos-2] = 'F';
    dfs(pos-2, lev+1);
    a[pos-2] = w - a[pos];
    a[pos] = 'F';
  }
  if(pos<n-1){
    a[pos] = a[pos+1];
    a[pos+1] = 'F';
    dfs(pos+1, lev+1);
    a[pos+1] = a[pos];
    a[pos] = 'F';
  }
  if(pos<n-2){
    a[pos] = w-a[pos+2];
    a[pos+2] = 'F';
    dfs(pos+2, lev+1);
    a[pos+2] = w-a[pos];
    a[pos] = 'F';
  }
}

int main(void)
{
  int cs=0;
  while(scanf("%s",a)!=EOF && a[0]!='-') {
    int r = 0, i;
    ++cs;
    for(n=0;a[n];n++);
    for(i=0;a[i];i++)
      if(a[i]=='F'){
        break;
      }
    mn = 10;
    dfs(i, 0);
    if(mn==10){
      printf("%d. -1\n", cs);
    }else{
      printf("%d. %d\n", cs, mn);
    }
  }
  return 0;
}
