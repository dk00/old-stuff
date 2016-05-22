#include <stdio.h>
#define MAXNUM 60
#define LEN 10
// pf

FILE *fin=freopen("pf.in","r",stdin);

class Symbol {
  public:
    char ch;
    char M[LEN+5][LEN+5];
    void R90(void) {
      int i,j;
      char T[LEN][LEN];
      for(i=0;i<LEN;i++)
        for(j=0;j<LEN;j++)
          T[i][j]=M[i][j];
      for(i=0;i<LEN;i++)
        for(j=0;j<LEN;j++)
          M[j][LEN-i-1]=T[i][j];
    }
};

int sn,len;
Symbol S[MAXNUM];
char Buff[20];

inline int Match(const Symbol &A,const Symbol &B)
{
  int i,j,c=0;
  for(i=0;i<LEN;i++)
    for(j=0;j<LEN;j++)
      if(A.M[i][j]==B.M[i][j]) c++;
  return c;
}

inline int Val(Symbol &A,const Symbol &B)
{
  int i,m,c=0;
  for(i=0;i<4;i++) {
    m=Match(A,B);
    if(m>c) c=m;
    A.R90();
  }
  return c;
}

inline void Process(Symbol& A)
{
  int i,max,ind,val;
  max=-1;
  for(i=0;i<sn;i++) {
    val=Val(S[i],A);
    if(val>max) {
      max=val;
      ind=i;
    }
  }
  printf("%c",S[ind].ch);
}

int main(void)
{
  int i,j;
  Symbol Im;
  while(scanf("%d",&sn)==1) {
    for(i=0;i<sn;i++) {
      scanf("%s",Buff);
      S[i].ch=Buff[0];
      for(j=0;j<LEN;j++)
        scanf("%s",S[i].M[j]);
    }
    scanf("%d",&len);
    for(i=0;i<len;i++) {
      for(j=0;j<LEN;j++)
        scanf("%s",Im.M[j]);
      Process(Im);
    }
    printf("\n");
  }
  return 0;
}
