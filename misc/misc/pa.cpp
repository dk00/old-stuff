#include <stdio.h>
#include <string.h>
#define MAXLEN 5005
//a

int n;
char S[MAXLEN];
char C[MAXLEN],T[MAXLEN];

int Compare(char *a,char *b)
{
  int la,lb;
  la=strlen(a);
  lb=strlen(b);
  if(la>lb) return -1;
  if(la<lb) return 1;
  return strcmp(a,b);
}

void Solve(void)
{
  int i,j;
  C[0]=0;
  // odd
  for(i=0;i<n;i++) {
    for(j=1;i-j>=0&&i+j<n;j++)
      if(S[i-j]!=S[i+j]) break;
    j--;
    strncpy(T,S+i-j,j*2+1);
    T[j*2+1]=0;
//    printf("[%d]",j);puts(T);puts(S);
    if(Compare(T,C)<0) strcpy(C,T);
  }
  // even
  for(i=0;i<n-1;i++) {
    for(j=1;i-j+1>=0&&i+j<n;j++)
      if(S[i-j+1]!=S[i+j]) break;
    j--;
    strncpy(T,S+i-j+1,j*2);
    T[j*2]=0;
    if(Compare(T,C)<0) strcpy(C,T);
  }
  puts(C);
}

int main(void)
{
  int t;
  int casenum=1;
  freopen("pa.in","r",stdin);
  scanf("%d",&t);
  gets(S);
  while(t--) {
    n=0;
    while(gets(S+n)&&strcmp(S+n,"End")) {
      n+=strlen(S+n);
    }
    S[n]=0;
    printf("Case %d: ",casenum++);
    Solve();
  }
  return 0;
}
