#include <stdio.h>

long long a[200005][2];
long long b[400005][2];

int cross(int x, int y){
  if(b[x][0]*b[y][1] > b[x][1]*b[y][0])
    return 1;
  else if(b[x][0]*b[y][1] == b[x][1]*b[y][0])
    return 0;
  else
    return -1;
}

int main(void)
{
  int n;
  int T, i;
  scanf("%d", &T);
  while(T--){
    scanf("%d", &n);
    for(i=0;i<n;i++){
      int x, y;
      scanf("%d%d", &x, &y);
      a[i][0] = (long long) x;
      a[i][1] = (long long) y;
    }
    a[n][0] = a[0][0];
    a[n][1] = a[0][1];
    for(i=0;i<n;i++)
    {
      b[i][0] = a[i+1][0] - a[i][0];
      b[i][1] = a[i+1][1] - a[i][1];
      b[n+i][0] = b[i][0];
      b[n+i][1] = b[i][1];
    }
    int sign;
    sign = cross(0, 1);
    int j = 1, mx = 0;
    for(i=0;i<n;i++){
      if(j<=i) j=i+1;
      while(j<i+n && cross(i, j) == sign) ++j;
      if(mx < j-i) mx = j-i;
    }
    printf("%d\n", mx);
  }
  return 0;
}
