#include<cstdio>
#include"game.h"
#include"interface.h"
Move search(Board S);
extern long long nodes;

main() {
  Board S;
  Move m;
  int d, x, y;
  char cmd[99];
  srand(time(NULL));
  interface_init();
  game_init();
  init(S);
  while (scanf("%s", cmd) == 1) {
    if (cmd[0] == 'p') {
      scanf("%s %d", cmd, &d);
      y = cmd[0]-'a';
      x = cmd[1]-'1';
      m.s = x*4 + y;
      d = valid(S, m.s, d);
      printf("%d\n", d);
      if (d && S.r0[S.turn-1] == 1) reveal(S, m.s);
      if (S.turn == 1 && (S.board[m.s]&1)) {
        S.log[1] = S.log[0];
        S.r0[1] = S.r0[0];
        ++S.turn;
      }
      display(S);
    }
    if (cmd[0] == 'u') {
      undo(S);
      display(S);
    }
    if (cmd[0] == 's') {
      unsigned t0 = GetTickCount();
      TL = 15000 + t0;
      Move m0 = search(S);
      t0 = GetTickCount() - t0;
      printf("%u\t%lld nodes/s\n", t0, nodes*1000/t0);
      x = m0.s;
      printf("%c%d ", 'a'+(x&3), 1+(x>>2));
      x = m0.t;
      printf("%c%d\n", 'a'+(x&3), 1+(x>>2));
      play(S, m0.s, m0.t);
      if (S.r0[S.turn-1] == 1) reveal(S, m0.s);
      if (S.turn == 1 && (S.board[m0.s]&1)) {
        S.log[1] = S.log[0];
        S.r0[1] = S.r0[0];
        ++S.turn;
      }      
      display(S);
    }
  }
}

/*
 1 2 3 4
 5 6 7 8
 9 
 
 ���� > �L�L�L�L�L
 �h�h > �L�L�L�L�L

 �h   > ��
 �h   > �ۧL�L�L�L�L

 �ӥK ? �h������
 �ӥK ? �h���

 �N�h�h�� > �ӥK�۬����ϽX�X�L

 �ӥK�� ? �h�h���


 �ӥK < �h�h���

 �ӥK > �H�H�������� x
 �ӥK > �H�H������   x+1
 �ӥK > �H������     x+2

���X���϶H�ۤh�K

 1 5 9
 2 6
 3 7
 4 8
 */
