#include<cstdio>
#include"game.h"
#include"interface.h"

int n;
int rank[999];

inline Score eval(const Board& S) {
  int_fast8_t i, j, k, l;
  const int Q[] = {512, 96, 64, 48, 32, 24, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0}, 
        J[] = {0, 0, 8, 16, 24, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
  Score r = 0;
  for (i = 1; i < NRank; ++i) {
    k = S.count[5];
    l = S.count[4];
    if (_cap[3][i*2]) {
      k += S.count[3]/2;
      l += S.count[2]/2;
    }
    for (j = 3; j < NRank; ++j) {
      if (_cap[j*2+1][i*2]) {
        k += S.count[j*2+1];
        l += S.count[j*2];
      }
    }
    r += Q[k]*S.count[i*2] - Q[l]*S.count[i*2+1];
  }
  if (S.turn&1) r = -r;
  return r;
}

int test() {
  char a[] = " *pPcCnNrRmMgGkK";
  char p[99];
  int i, j, k, l, r;

  for (i = 0; a[i]; ++i) {
    rank[a[i]] = i;
  }
  Board S;
  S.turn = 0;
  uint_fast8_t *count = S.count;
  while (scanf("%s", p) == 1) {
    for (i = 0; i < NRank*2; ++i)
      count[i] = 0;
    for (i = 0; p[i]; ++i)
      count[rank[p[i]]]++;
    printf("%d\n", eval(S));
  }
}

void test1() {
  const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
  int i, j, x, y;
  for (i = 0; i < 32; ++i) {
    printf("{");
    for (j = 0; j < 4; ++j) {
      x = i/4 + dx[j];
      y = i%4 + dy[j];
      if (x < 0 || x >= 8 || y < 0 || y >= 4)
        printf(" N");
      else
        printf("%2d", x*4 + y);
      if (j < 3) printf(", ");
    }
    printf("}, ");
  }
}

/*
pppppccnnrrmmggkPPPPPCCNNRRMMGGK

ppppccnnkkmmggkPPPPPCCNNKKMMGGK

pccnnkkmmggkPPPPPCCNNKKMMGGK
*/

main(int argc, char **argv) {
/*  Board S;
  init(S);
  loadboard(S, argv[1]);*/

  GetTickCount();
  test();


}
