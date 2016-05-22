#include <stdio.h>
#include <algorithm>
using namespace std;

int main(void)
{
  long long a[1000], b[1000];
  int i;
  for(i=0;i<3;i++)
    scanf("%lld", &a[i]);
  int c=1;
  while(1){
    sort(a, a+2+c);
    for(i=0;i<1+c;i++)
      b[i] = a[i+1]-a[i];
    for(i=1;i<1+c;i++)
      if(b[i] < b[0])
        b[0] = b[i];
    if(b[0]==0) break;
    a[c+2] = b[0];
    ++c;
  }
  printf("%d\n", c);
}
