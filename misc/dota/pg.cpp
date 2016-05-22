#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int s[N],p[N];
main()
{
  int i,j,n,m;
  while(scanf("%d %d",&n,&m)>0)
  {
    for(i=0;i<n;i++)
      p[i]=i,s[i]=n;
    while(m--)
    {
      scanf("%d %d",&i,&j);
      i--,j--;
      if(i>j)swap(i,j);
      p[j]<?=i;
    }
    for(m=0,i=n-1;i>=0;i--)
    {
      for(j=0;s[j]<=i;j++);
      m>?=j;
      s[j]=p[i];
    }
    printf("%d\n",m+1);
  }
}
