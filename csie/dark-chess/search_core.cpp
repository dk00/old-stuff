#include<stdint.h>
#include"game.h"
#include"interface.h"
#include<cstdio>
#include<cstring>
int MAXD = 4, PL = 20, RL = 4;
long long MAXN = 100000000ll;
long long nodes;

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

int END = 0;
inline bool term(const Board& S, int depth) {
  if (depth <= 0 || END)
    return true;
  return false;
}

struct Move_Iter {
  Pos p;
  int_fast8_t d, i;
};

int hn = 24;
Move HT[2][99], K0[99][99];
void ht_mem(uint_fast8_t pl, Move m, Score sc) {
  int i, j;
  for (i = 0; i < hn; ++i)
    if (HT[pl][i].s == m.s && HT[pl][i].t == m.t)
      break;
  for (;i > 0; --i)
    HT[pl][i] = HT[pl][i-1];
  HT[pl][0] = m;
}

void init(const Board& S, Move_Iter& m, Move K[]) {
  m.i = 0;
  m.d = 0;
  m.p = N;
  for (int i = 0; i < hn; ++i)
    K[i] = HT[S.turn&1][i];
}
bool next(const Board& S, Move_Iter& m, Move K[]) {
  if (m.i < hn) {
    m.p = K[m.i].s;
    m.d = K[m.i].t;
    ++m.i;
    return true;
  }
  if (m.i == hn) {
    ++m.i;
    m.p = N;
  }
  if (--m.d >= 0) return true;
  while (--m.p >= 0 && (S.board[m.p] < 1 ||(S.board[m.p] > 1 
          && (S.board[m.p]&1) != (S.turn&1))));
  if (m.p < 0) return false;
  m.d = 3;
  if (S.board[m.p]/2 == 2) m.d = 7;
  if (S.board[m.p] == 1) m.d = 0;
  return true;
}

inline bool danger(const Board& S, Pos p) {
  Rank k = (14|(S.turn&1));
  if (S.board[p] != 1 || (S.c0[k^1]+S.c0[3-(S.turn&1)] < 1)) return false;
  for (int i = 0; i < 4; ++i)
    if (S.board[adj[p][i]] == k) return true;
  return false;
}

#define _NEGA_SCOUT
Hash_Entry H[HASHSIZE];
Move m0;
Score go(Board& S, Score lb, Score ub, int_fast8_t depth) {
  ++nodes;
  if (!(nodes&0xFFFF) && GetTickCount() >= TL) END = 1;
  Score m = -inf, t, base = eval(S);
  if (term(S, depth)) {
    return base;
  }
  //rules: draw
  if (S.peace[S.turn] >= PL || S.rep[S.turn] >= RL)
    return 0;
  //reveal p b3 0 p b4 0 p b5 0 p c4 0 p c3 0
  if (S.r0[S.turn-1] == 1 && S.board[S.log[S.turn-1].s] == 0) {
    int i, j, un, ln, sum = 0;
    long long sb = 0;
    for (i = 2; i < 16; ++i) {
      if (S.c0[i] < 1) continue;
      sum += S.c0[i];
      _reveal(S, S.log[S.turn-1].s, i);
      j = go(S, lb, ub, depth);
      if (j >= ub) un += (S.c0[i]+1);
      if (j <= lb) ln += (S.c0[i]+1);
      j *= (S.c0[i]+1);
      sb += j;
      _remove(S, S.log[S.turn-1].s);
    }
    S.board[S.log[S.turn-1].s] = 0;
    //if (un >= ln*2 && un*3 >= sum) return ub;
    //if (ln >= un*2 && ln*3 >= sum) return lb;
    if (sum > 0) sb /= sum;
    return sb;
  }

  Hash_Entry h0;
  if (hash_get(H, S, h0) && h0.depth >= depth) {
    m = h0.sc;
    if (h0.type) return m;
  }
  Move_Iter mi;
  Move a;
  //XXX move gen
  init(S, mi, K0[depth]);
  while (next(S, mi, K0[depth])) {
    if (danger(S, mi.p)) continue;
    if (!valid(S, mi.p, mi.d)) continue;
    t = m;
    if (lb > m) t = lb;
    #ifdef _NEGA_SCOUT
    if (S.r0[S.turn-1] != 1)
      t = -go(S, -t-1, -t, depth-1);
    if (S.r0[S.turn-1] == 1 || (t > m && t < ub && depth >= 3))
    #endif 
      t = -go(S, -ub, -t, depth-1);
    undo(S);
    if (t > m) a.s = mi.p, a.t = mi.d, m = t;
    if (depth == MAXD)
      printf("%c%d %d %d %d\n", 'a'+(mi.p&3), 1+(mi.p>>2), mi.d, t, m);
    if (t >= ub) break;
  }
  m0 = a;
  if (m >= lb)
    hash_set(H, S, depth, m, m < ub);
  if (m >= ub) ht_mem(S.turn&1, a, m);
  return m;
}

Move search(Board S) {
  nodes = 0;
  Move m1;
  Score t = -inf;
  memset(H, 0, sizeof(H));
  END = 0;
  for (MAXD = 2; !END && MAXD <= 999; ++MAXD) {
    printf(">> %d\n", MAXD);
    m1 = m0;
    if (t >= inf) break;
    t = go(S, -inf, inf, MAXD);
  }
  printf("%d %d nodes\n", MAXD, nodes);
  if (S.board[m1.s] == 1) m1.t = m1.s;
  else if (m1.t >= 4) m1.t = jump(S, m1.s, m1.t-4);
  else m1.t = m1.s + dx[m1.t];
  return m1;
}
