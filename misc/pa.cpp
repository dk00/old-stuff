#include <stdio.h>
#include <algorithm>
#define IN(v) (v)
#define OUT(v) (n+2+v)
#define SOURCE OUT(0)
#define SINK IN(n+1)
#define NODENUM (n*2+4)
#define MAXNUM (206*2)
#define MAXEDGE (MAXNUM*MAXNUM)
// pa

FILE *fin=freopen("pa.in","r",stdin);

class Edge {
  public:
    int v,u;
    int len;
    const bool operator<(const Edge &B) const {
      return len<B.len;
    }
};

int n,m,flow,k;
Edge E[MAXEDGE];
int ADJnum[MAXNUM],ADJ[MAXNUM][MAXNUM],Res[MAXNUM][MAXNUM];

int ql,qr,Q[MAXNUM],Pred[MAXNUM];
bool Visited[MAXNUM];

inline int Swap(int *a,int *b)
{
  int t=*a;
  *a=*b;
  *b=t;
}

inline void Init(void)
{
  int i,j;
  for(i=0;i<NODENUM;i++)
    ADJnum[i]=0;
  for(i=0;i<NODENUM;i++)
    for(j=0;j<NODENUM;j++)
      Res[i][j]=0;
  for(i=0;i<=n+1;i++) {
    ADJ[IN(i)][ADJnum[IN(i)]++]=OUT(i);
    ADJ[OUT(i)][ADJnum[OUT(i)]++]=IN(i);
    Res[IN(i)][OUT(i)]=1;
  }
}

inline void Append_Edge(Edge &e)
{
  ADJ[OUT(e.v)][ADJnum[OUT(e.v)]++]=IN(e.u);
  ADJ[IN(e.u)][ADJnum[IN(e.u)]++]=OUT(e.v);
  Res[OUT(e.v)][IN(e.u)]++;
}

inline bool BFS(void)
{
  int i,v,nv;
  for(i=0;i<NODENUM;i++)
    Visited[i]=0;
  ql=0;
  qr=1;
  Q[0]=SOURCE;
  Visited[SOURCE]=1;
  while(ql<qr) {
    v=Q[ql];
    if(v==SINK) return 1;
    for(i=0;i<ADJnum[v];i++) {
      nv=ADJ[v][i];
      if(Visited[nv]||Res[v][nv]<=0) continue;
      Pred[nv]=v;
      Visited[nv]=1;
      Q[qr++]=nv;
    }
    ql++;
  }
  return 0;
}

void Augment(void)
{
  int v=SINK;//printf("aug: ");
  while(v!=SOURCE) {//printf("%d ",v);
    Res[Pred[v]][v]--;
    Res[v][Pred[v]]++;
    v=Pred[v];
  }//printf("\n");
  flow++;
}

inline void Flow(void)
{
  while(BFS())
    Augment();
}

inline int Minimum_Degree(void)
{
  int i;
  Init();
  std::sort(E,E+m);
  flow=0;
  for(i=0;i<m;i++) {
    Append_Edge(E[i]);
    Flow();//printf("[%d]\n",flow);
    if(flow>=k) return E[i].len;
  }
  return -1;
}

int main(void)
{
  int casenum=1;
  int i,v,u,val;
  while(scanf("%d",&n)==1&&n) {
    scanf("%d",&m);
    for(i=0;i<m;i++) {
      scanf("%d %d %d",&E[i].v,&E[i].u,&E[i].len);
      if(E[i].v>E[i].u) Swap(&E[i].v,&E[i].u);
    }
    scanf("%d",&k);
    val=Minimum_Degree();
    printf("Case %d: ",casenum++);
    if(val<0) printf("no solution\n");
    else printf("%d\n",val);
  }
  return 0;
}
