#include <stdio.h>
#define MAXNUM 20050
#define MAXEDGE 2000005
#define MAXLEN 10000
#define MOD 10000
#define PRTSTR "%04d"

inline int Max(int a,int b)
{
  return a>b?a:b;
}

class Bignum {
  public:
    int len;
    int s[MAXLEN];
    Bignum() {}
    Bignum(int x) {
      len=0;
      while(x) {
        s[len++]=x%MOD;
        x/=MOD;
      }
    }
    void Print(void) {
      int i;
      if(len) {
        printf("%d",s[len-1]);
        for(i=len-2;i>=0;i--)
          printf(PRTSTR,s[i]);
        printf("\n");
      } else printf("0\n");
    }
    Bignum& operator*=(const int b) {
      int i;
      long long res,carry=0;
      for(i=0;i<len||carry;i++) {
        res=(long long)(i<len?s[i]:0)*b+carry;
        carry=res/MOD;
        s[i]=res%MOD;
      }
      len=i;
      return *this;
    }
    const Bignum operator*(const int &b) const {
      return (Bignum)*this*=b;
    }
};

class Edge {
  public:
    int v,u;
};

int n,en;
Edge e[MAXEDGE];
int deg[MAXNUM],*adj[MAXNUM];

int ste,stv;
int low[MAXNUM],dfa[MAXNUM];
bool visited[MAXNUM];
int vs[MAXNUM];
Edge es[MAXEDGE];

int vc,ec,visn;
bool fail;
Bignum sol;

inline int Min(int a,int b)
{
  return a<b?a:b;
}

void DFS(int v,int pred,int d)
{
  int i,u;
  visn++;
  visited[v]=1;
  low[v]=dfa[v]=d;
  vs[stv++]=v;
  for(i=0;i<deg[v];i++) {
    u=adj[v][i];
    if(u==pred) continue;
    if(visited[u]) {
      if(dfa[u]<dfa[v]) {
        es[ste].v=v;
        es[ste++].u=u;
      }
      low[v]=Min(low[v],dfa[u]);
    } else {
      es[ste].v=v;
      es[ste++].u=u;
      DFS(u,v,d+1);
      low[v]=Min(low[v],low[u]);
      if(low[u]>=dfa[v]) {
        vc=0;
        ec=0;
        while(vs[stv-1]!=v) {
          stv--;
          vc++;
        }
        vc++;
        while(es[ste-1].v!=v||es[ste-1].u!=u) {
          ste--;
          ec++;
//          printf("%d %d\n",es[ste].v,es[ste].u);
        }
        ste--;
        ec++;
//        printf("%d %d\n",es[ste].v,es[ste].u);
        if(vc<ec) fail=1;
        if(ec>1) sol*=ec+1;//printf("[%d %d %d %d]\n",v,u,vc,ec);
      }
    }
  }
}

inline void Solve(void)
{
  int i;
  sol=Bignum(1);
  fail=0;
  visn=0;
  for(i=1;i<=n;i++)
    visited[i]=0;
  ste=stv=0;
  DFS(1,0,0);
  if(visn!=n||fail) printf("0\n");
  else sol.Print();
}

int main(void)
{
  int i,j,pn,pl,v,u;
//  Bignum a(4671037),b(1000),c;
//  c=a;
//  c*=28001;
//  c.Print();
  while(scanf("%d %d",&n,&pn)==2) {
    en=0;
    for(i=1;i<=n;i++)
      deg[i]=0;
    for(i=0;i<pn;i++) {
      scanf("%d",&pl);
      scanf("%d",&v);
      for(j=1;j<pl;j++) {
        scanf("%d",&u);
        e[en].v=v;
        e[en++].u=u;
        deg[v]++;
        deg[u]++;
        v=u;
      }
    }
    for(i=1;i<=n;i++) {
      adj[i]=new int[deg[i]];
      deg[i]=0;
    }
    for(i=0;i<en;i++) {
      adj[e[i].v][deg[e[i].v]++]=e[i].u;
      adj[e[i].u][deg[e[i].u]++]=e[i].v;
    }
    Solve();
    for(i=1;i<=n;i++)
      delete [] adj[i];
  }
  return 0;
}
