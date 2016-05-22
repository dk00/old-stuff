#include"game.h"
#include"interface.h"
Move search(Board S);

int main() {
  unsigned t0 = GetTickCount();
  interface_init();
  game_init();
  Board S;
  init(S);
  loadboard(S, "board.txt");
  display(S);
  TL += t0;
  Move m = search(S);
  play(m);
  return 0;
}
