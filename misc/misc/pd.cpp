#include <stdio.h>
#define MAXNUM 2005
// pd

FILE *fin=freopen("pd.in","r",stdin);

int n,m;
int ADJnum[MAXNUM],ADJ[MAXNUM][MAXNUM];
int RDJnum[MAXNUM],RDJ[MAXNUM][MAXNUM];
int o,Order[MAXNUM];
bool Visited[MAXNUM];

void DFS_Order(int v)
{
  int i;
  Visited[v]=1;
  for(i=0;i<ADJnum[v];i++)
    if(!Visited[ADJ[v][i]]) DFS_Order(ADJ[v][i]);
  Order[o++]=v;
}

void DFS_Reverse(int v)
{
  int i;
  Visited[v]=1;
  for(i=0;i<RDJnum[v];i++)
    if(!Visited[RDJ[v][i]]) DFS_Reverse(RDJ[v][i]);
}

inline int SCC_Num(void)
{
  int i,sn=0;
  for(i=1;i<=n;i++)
    Visited[i]=0;
  o=0;
  for(i=1;i<=n;i++)
    if(!Visited[i]) DFS_Order(i);
  for(i=1;i<=n;i++)
    Visited[i]=0;
  for(i=n-1;i>=0;i--) {
    if(!Visited[Order[i]]) {
      DFS_Reverse(Order[i]);
      sn++;
    }
  }
  return sn;
}

int main(void)
{
  int t;
  int i,v,u,buff;
  scanf("%d",&t);
  while(t--) {
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
      ADJnum[i]=RDJnum[i]=0;
    for(i=0;i<m;i++) {
      scanf("%d %d",&v,&u);
      ADJ[v][ADJnum[v]++]=u;
      RDJ[u][RDJnum[u]++]=v;
    }
    printf("%d\n",SCC_Num());
    scanf("%d",&buff);
  }
  return 0;
}
