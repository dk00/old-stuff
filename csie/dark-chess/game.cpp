#include"game.h"
#include<stdlib.h>
Hash zv[N*NRank*2], zv1[N*NRank*2];
uint_fast8_t path_count[HASHSIZE];
void game_init() {
  int i, j;
  for (i = 0; i <= N*NRank*2; ++i) {
    if (i%(NRank*2) == 0) {
      zv[i] = 0;
      continue;
    }
    for (j = 0; j < 5; ++j) {
      zv[i] = (zv[i]<<13)|rand();
      zv1[i] = (zv1[i]<<13)|rand();
    }
  }
}

void init(Board& S) {
  const Rank def[35] = {2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15};
  S.z = S.peace[0] = S.rep[0] = S.peace[1] = S.rep[1] = S.turn = 0;
  for (int i = 0; i < NRank*2; ++i)
    S.count[i] = S.c0[i] = 0;
  for (int i = 0; i < N; ++i) {
    S.board[i] = 1;
    ++S.count[def[i]];
    ++S.c0[def[i]];
  }
}

void reveal(Board& S, Pos p, Rank r) {
  if (r == 1) {
    int n = 0;
    for (r = 2; r < 16; ++r)
      n += S.c0[r];
    n = rand()%n;
    for (r = 2; n >= S.c0[r]; ++r)
      n -= S.c0[r];
  }
  _reveal(S, p, r);
}

