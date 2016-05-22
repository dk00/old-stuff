#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main(void)
{
  char a[1005], b[1005];
  while(scanf("%s%s", a, b)!=EOF){
    int c[128]={0};
    int d[128]={0}, i;
    int f=0;
    if(strlen(a) != strlen(b)) f = 1;
    for(i=0;a[i];i++)
      c[a[i]]++;
    for(i=0;b[i];i++)
      d[b[i]]++;
    sort(c, c+128);
    sort(d, d+128);
    for(i=0;i<128;i++){
      if(c[i]!=d[i])
      {f=1;break;}
    }
    if(f==1) printf("NO\n");
    else printf("YES\n");
  }
  return 0;
}
