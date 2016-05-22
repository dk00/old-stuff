#ifndef _GAME_H
#define _GAME_H
#include<cstdlib>
#include<stdint.h>
typedef int_fast8_t Pos;
//typedef uint_fast8_t Move;
typedef int_fast8_t Rank;
typedef uint_fast64_t Hash;

const int Width = 4, Height = 8, N = Height*Width, NRank = 8, NTurn = 256;
const int dx[] = {-4, 1, 4, -1};
const int adj[][4] = {
  { N,  1,  4,  N}, { N,  2,  5,  0}, { N,  3,  6,  1}, { N,  N,  7,  2},
  { 0,  5,  8,  N}, { 1,  6,  9,  4}, { 2,  7, 10,  5}, { 3,  N, 11,  6},
  { 4,  9, 12,  N}, { 5, 10, 13,  8}, { 6, 11, 14,  9}, { 7,  N, 15, 10},
  { 8, 13, 16,  N}, { 9, 14, 17, 12}, {10, 15, 18, 13}, {11,  N, 19, 14},
  {12, 17, 20,  N}, {13, 18, 21, 16}, {14, 19, 22, 17}, {15,  N, 23, 18},
  {16, 21, 24,  N}, {17, 22, 25, 20}, {18, 23, 26, 21}, {19,  N, 27, 22},
  {20, 25, 28,  N}, {21, 26, 29, 24}, {22, 27, 30, 25}, {23,  N, 31, 26},
  {24, 29,  N,  N}, {25, 30,  N, 28}, {26, 31,  N, 29}, {27,  N,  N, 30},
  { N,  N,  N,  N}};
const int _cap[][NRank*2] = { 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
  {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
  {1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}
};

struct Move {Pos s, t; };
struct Board {
  //XXX first move (color)
  uint_fast8_t turn;
  Rank board[N+1];
  uint_fast8_t row[Height], col[Width];
  uint_fast8_t count[NRank*2], c0[NRank*2], rep[N*64], peace[N*64];
  Rank r0[NTurn];
  Move log[N*64], moves[N*64];
  Hash z;
};
typedef int_fast16_t Score;
const Score inf = (1<<15)-32;
const int HASHSIZE = 2<<20;
struct Hash_Entry {
  Hash z;
  int_fast8_t depth, type;
  Score sc;
};
extern Hash zv[N*NRank*2], zv1[N*NRank*2];
extern uint_fast8_t path_count[HASHSIZE];
inline uint_fast32_t hash_val(Hash z) {
  return ((z>>44)^(z>>29)^(z>>15)^z)&(HASHSIZE-1);
}
inline bool hash_get(const Hash_Entry H[], const Board& S, Hash_Entry& h0) {
  Hash z0 = S.z^zv1[32-(S.turn&1)]^zv1[16+S.rep[S.turn]]^zv1[S.peace[S.turn]];
  uint_fast32_t v = hash_val(z0);
  h0 = H[v];
  return H[v].z == z0;
}
inline void hash_set(Hash_Entry H[], const Board& S, int_fast8_t depth, Score sc, uint_fast8_t type) {
  Hash z0 = S.z^zv1[32-(S.turn&1)]^zv1[16+S.rep[S.turn]]^zv1[S.peace[S.turn]];
  uint_fast32_t v = hash_val(z0);
  if (depth > H[v].depth || (H[v].z == z0 && H[v].depth == depth && sc > H[v].sc)) {
    H[v].z = z0;
    H[v].depth = depth;
    H[v].sc = sc;
    H[v].type = type;
  }
}

inline void undo(Board& S) {
  uint_fast32_t i = hash_val(S.z);
  --path_count[i];  
  --S.turn;
  Move& m0 = S.log[S.turn];
  S.board[m0.s] = S.board[m0.t];
  S.z ^= zv[m0.t*NRank*2+S.board[m0.t]];
  if (m0.s != m0.t) S.z ^= zv[m0.s*NRank*2+S.board[m0.t]];
  if (S.r0[S.turn]) S.z ^= zv[m0.t*NRank*2+S.r0[S.turn]];
  if (S.r0[S.turn] == 1) ++S.c0[S.board[m0.s]];
  S.board[m0.t] = S.r0[S.turn];
  ++S.count[S.r0[S.turn]];
}
//XXX hash
inline void play(Board& S, Pos from, Pos to) {
  --S.count[S.board[to]];
  S.log[S.turn].s = from;
  S.log[S.turn].t = to;
  if (S.board[to] >= 1) S.peace[S.turn+1] = 0;
  else S.peace[S.turn+1] = S.peace[S.turn] + 1;
  if (S.board[to]) S.z ^= zv[to*NRank*2+S.board[to]];
  S.z ^= zv[from*NRank*2+S.board[from]];
  S.z ^= zv[to*NRank*2+S.board[from]];
  S.r0[S.turn] = S.board[to];
  S.board[to] = S.board[from];
  S.board[from] = 0;
  ++S.turn;

  uint_fast32_t i = hash_val(S.z);
  S.rep[S.turn] = path_count[i]++;
}

inline void _reveal(Board& S, Pos p, Rank r) {
  --S.c0[r];
  S.board[p] = r;
  S.z ^= zv[p*NRank*2+r];
}
inline void _remove(Board& S, Pos p) {
  S.z ^= zv[p*NRank*2+S.board[p]];
  ++S.c0[S.board[p]];
}
inline Pos jump(Board& S, Pos s, uint_fast8_t d) {
  for (s = adj[s][d]; s != N; s = adj[s][d])
    if (S.board[s]) break;
  for (s = adj[s][d]; s != N; s = adj[s][d])
    if (S.board[s]) break;
  return s;
}

inline bool valid(Board& S, Pos s, uint_fast8_t d) {
  Pos t = adj[s][d];
  if (S.board[s] == 1) {
    if (d) return false;
    play(S, s, s);
    return true;
  }
  if (t >= N || (S.board[s]&1)!=(S.turn&1)) return false;
  if (d >= 4) {
    if (S.board[s]/2 != 2) return false;
    t = jump(S, s, d%4);
    if (t >= N) return false;
    if (S.board[t] == 1 ||(S.board[s]&1)==(S.board[t]&1)) return false;
  }
  else if (!_cap[S.board[s]][S.board[t]]) return false;
  play(S, s, t);
  return true;
}

void reveal(Board& S, Pos p, Rank r = 1);
void game_init();
void init(Board& S);
#endif
