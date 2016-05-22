#include<cstdio>
#include<vector>
using namespace std;
const int N=10001;
vector<int> c[N];
int ow[N],w[N],path[N];
int calc(int v)
{
  for(int i=0;i<c[v].size();i++)
    w[v]+=calc(c[v][i]);
  return w[v];
}
int go(int v,int d)
{
  int i,j,sum=0;
  path[d]=v;
  path[d+1]=-1;
  if(c[v].size()<1)return ow[v];
  for(i=0,j=c[v][0];i<c[v].size();i++)
    if(w[c[v][i]]>w[j] ||(w[c[v][i]]==w[j] && c[v][i]>j))
      j=c[v][i];
  return ow[v]+go(j,d+1);
}
main()
{
  freopen("pi.in","r",stdin);
  int i,j,k,n,r,T;
  scanf("%d",&T);
  while(T--)
  {
    scanf("%d %d",&n,&r);
    for(i=0;i<n;i++)
    {
      scanf("%d",w+i);
      ow[i]=w[i];
      scanf("%d",&j);
      c[i].clear();
      while(j--)
      {
        scanf("%d",&k);
        c[i].push_back(k);
      }
    }
    calc(r);
    printf("%d\n",go(r,0));
    for(i=0;path[i]>=0;i++)
    {
      if(i%10)putchar(' ');
      printf("%d",path[i]);
      if(i%10==9)puts("");
    }
    if(i%10)puts("");
  }
}
