#include <stdio.h>
#include <string.h>
#define NX(x,y,z) (4*(x)+2*(z))
#define NY(x,y,z) (3*(y)+2*(z));
#define MAXNUM 55
// pa

int ynum,xnum,maxz;
int H[MAXNUM][MAXNUM];
char S[MAXNUM*4][MAXNUM*4];

inline void Put(int x,int y)
{
  int i,j;
  S[x][y]=S[x+4][y]=S[x][y+3]=S[x+4][y+3]='+';
  S[x+1][y+4]=S[x+5][y+1]=S[x+5][y+4]='/';
  S[x][y+1]=S[x][y+2]=S[x+4][y+1]=S[x+4][y+2]=S[x+6][y+3]=S[x+6][y+4]='|';
  for(i=0;i<3;i++)
    S[x+i+1][y]=S[x+i+1][y+3]=S[x+i+3][y+5]='-';
  for(i=0;i<3;i++)
    S[x+i+2][y+4]=S[x+i+1][y+2]=S[x+i+1][y+1]=' ';
  S[x+5][y+2]=S[x+5][y+3]=' ';
}

inline void Print(int xl,int yl)
{
  int i;
  for(i=yl-1;i>=0;i--) {
    for(j=0;j<xl;j++) {
      printf("%c",S[j][i]);
    }
    printf("\n");
  }
}

inline void Set(void)
{
  int x,y,z;
  memset(S,'.',sizeof(S));
  for(z=0;z<maxz;z++) {
    for(y=maxy;y>=0;y--) {
      
    }
  }
}

int main(void)
{
  int i,j;
  while(scanf("%d %d",&ynum,&xnum)==2) {
    maxz=0;
    for(i=ynum-1;i>=0;i--) {
      for(j=0;j<xnum;j++) {
        scanf("%d",H[j]+i);
        maxz>?=H[j][i];
      }
    }
  }
  return 0;
}
