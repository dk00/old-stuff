#include <stdio.h>
#include <algorithm>
#define MAXNUM 105
#define MAXPRO 1005
#define INF 100000000
// ph

FILE *fin=freopen("ph.in","r",stdin);

class Station {
  public:
    int s,p;
};

int ln,rn,maxtime;
int P[MAXPRO][MAXNUM][MAXNUM][2];
Station L[MAXNUM],R[MAXNUM];

inline int Dist(int x,int y)
{
  if(x<y) return y-x;
  else return x-y;
}

inline int Max(int a,int b)
{
  return (a>b?a:b);
}

inline void Maxify(int &a,const int b)
{
  if(b>a) a=b;
}

inline int Max_Profit(void)
{
  int i,l,r,t,maxp=0;
  for(l=0;l<=ln;l++)
    for(r=0;r<=rn;r++)
      P[0][l][r][0]=P[0][l][r][1]=-INF;
  P[0][0][0][0]=P[0][0][0][1]=0;
  for(t=1;t<=maxtime;t++) {
    for(l=0;l<=ln;l++) {
      for(r=0;r<=rn;r++) {
        P[t][l][r][0]=-INF;
        if(l>0&&t>=Dist(L[l-1].s,L[l].s))
          Maxify(P[t][l][r][0], P[t-Dist(L[l-1].s,L[l].s)][l-1][r][0]+Max(0,L[l].p-t));
        if(l>0&&t>=Dist(L[l].s,R[r].s))
          Maxify(P[t][l][r][0], P[t-Dist(L[l].s,R[r].s)][l-1][r][1]+Max(0,L[l].p-t));
          //
        P[t][l][r][1]=-INF;
        if(r>0&&t>=Dist(R[r-1].s,R[r].s))
          Maxify(P[t][l][r][1], P[t-Dist(R[r-1].s,R[r].s)][l][r-1][1]+Max(0,R[r].p-t));
        if(r>0&&t>=Dist(L[l].s,R[r].s))
          Maxify(P[t][l][r][1], P[t-Dist(R[r].s,L[l].s)][l][r-1][0]+Max(0,R[r].p-t));
        maxp>?=P[t][l][r][0];
        maxp>?=P[t][l][r][1];
      }
    }
  }
  return maxp;
}

bool Compare_Asc(const Station &a,const Station &b)
{
  return a.s<b.s;
}

bool Compare_Des(const Station &a,const Station &b)
{
  return a.s>b.s;
}

int main(void)
{
  int t,casenum;
  int i;
  scanf("%d",&t);
  for(casenum=1;casenum<=t;casenum++) {
    scanf("%d %d",&ln,&rn);
    maxtime=0;
    L[0].s=R[0].s=0;
    L[0].p=R[0].p=0;
    for(i=1;i<=ln;i++) {
      scanf("%d %d",&L[i].s,&L[i].p);
      L[i].s=-L[i].s;
      if(L[i].p>maxtime) maxtime=L[i].p;
    }
    for(i=1;i<=rn;i++) {
      scanf("%d %d",&R[i].s,&R[i].p);
      if(R[i].p>maxtime) maxtime=R[i].p;
    }
    std::sort(L,L+ln+1,Compare_Des);
    std::sort(R,R+rn+1,Compare_Asc);
    //for(i=0;i<=ln;i++)
//      printf("%d ",L[i].s);printf("\n");
//    for(i=0;i<=rn;i++)
//      printf("%d ",R[i].s);printf("\n");
    printf("Case %d: ",casenum);
    printf("%d\n",Max_Profit());
    scanf("%*d");
  }
  return 0;
}
