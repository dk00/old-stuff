#include <stdio.h>
#include <algorithm>
using namespace std;

int a[100005];

int main(void)
{
  int n, i;
  while(scanf("%d", &n)!=EOF)
  {
    int m = 0, x, y;
    for(i=0;i<n;i++) {
      scanf("%d%d", &x, &y);
      a[m++] = x*2;
      a[m++] = y*2+1;
    }
    sort(a, a+m);
    int mx=0, sum=0;
    for(i=0;i<m;i++){
      if(a[i] & 1)
        --sum;
      else if(++sum > mx)
        mx = sum;
    }
    printf("%d\n", mx);
  }
  return 0;
}
