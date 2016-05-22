#include <stdio.h>
#define SEG(a,b) (Sum[b]-Sum[a]+S[a])
#define COST(l,r,x) ABS(S[x]*((r)-(l)+1)-SEG(l,r))
#define MAXNUM 320
#define INF 1000000000
// pd

int n,p;
int S[MAXNUM],Sum[MAXNUM];
int C[MAXNUM][MAXNUM];

inline int ABS(int x)
{
  return (x>0?x:0-x);
}

inline int Min_Cost(void)
{
  int i,j,k,num,min;
  for(i=0;i<n;i++) {
    C[i][1]=COST(0,i,i);
    for(num=2;num<=p&&num<=i+1;num++) {
      C[i][num]=INF;
      for(j=i-1,k=i;j>=0&&j>=num-2;j--) {
        while(k>0&&ABS(S[i]-S[k-1])<ABS(S[j]-S[k-1]))
          k--;
        C[i][num]<?=C[j][num-1]+COST(j,k-1,j)+COST(k,i,i);
      }
    }
  }
  min=INF;
  for(i=p-1;i<n;i++)
    min<?=C[i][p]+COST(i,n-1,i);
  return min;
}

int main(void)
{
  int i;
  while(scanf("%d %d",&n,&p)==2) {
    for(i=0;i<n;i++)
      scanf("%d",S+i);
    Sum[i]=S[i];
    for(i=1;i<n;i++)
      Sum[i]=Sum[i-1]+S[i];
    printf("%d\n",Min_Cost());
  }
  return 0;
}
