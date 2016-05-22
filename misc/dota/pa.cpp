#include <stdio.h>
#include <string.h>
#define NX(x,y,z) (4*(x)+2*(z))
#define NY(x,y,z) (3*(y)+2*(z))
#define MAXNUM 55
// pa

int znum,xnum,maxy;
int pmx,pmy,pnx,pny;
int H[MAXNUM][MAXNUM];
char S[MAXNUM*4][MAXNUM*4];

inline void Put(int x,int y)
{
  int i,j;
  S[x][y]=S[x+4][y]=S[x][y+3]=S[x+4][y+3]=S[x+2][y+5]=S[x+6][y+5]=S[x+6][y+2]='+';
  S[x+1][y+4]=S[x+5][y+1]=S[x+5][y+4]='/';
  S[x][y+1]=S[x][y+2]=S[x+4][y+1]=S[x+4][y+2]=S[x+6][y+3]=S[x+6][y+4]='|';
  for(i=0;i<3;i++)
    S[x+i+1][y]=S[x+i+1][y+3]=S[x+i+3][y+5]='-';
  for(i=0;i<3;i++)
    S[x+i+2][y+4]=S[x+i+1][y+2]=S[x+i+1][y+1]=' ';
  S[x+5][y+2]=S[x+5][y+3]=' ';
  pmx>?=x+6;
  pmy>?=y+5;
  pnx<?=x;
  pny<?=y;
}

inline void Print(int xs,int ys,int xl,int yl)
{
  int i,j;
  for(i=yl;i>=ys;i--) {
    for(j=xs;j<=xl;j++) {
      printf("%c",S[j][i]);
    }
    printf("\n");
  }
}

inline void Set(void)
{
  int x,y,z;
  memset(S,'.',sizeof(S));
  pmx=pmy=0;
  pnx=pny=MAXNUM*10;
  for(y=0;y<maxy;y++) {
    for(z=znum-1;z>=0;z--) {
      for(x=0;x<xnum;x++) {
        if(H[x][z]>y) Put(NX(x,y,z),NY(x,y,z));
      }
    }
  }
  Print(pnx,pny,pmx,pmy);
}

int main(void)
{
  int i,j;
  while(scanf("%d %d",&znum,&xnum)==2) {
    maxy=0;
    for(i=znum-1;i>=0;i--) {
      for(j=0;j<xnum;j++) {
        scanf("%d",H[j]+i);
        maxy>?=H[j][i];
      }
    }
    Set();
  }
  return 0;
}
