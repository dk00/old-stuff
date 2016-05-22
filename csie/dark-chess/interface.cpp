#include<ctime>
#include<cstdio>
#include"game.h"
#include"interface.h"

unsigned TL = 15000;
Rank ch2rank[128];

void interface_init() {
  for (int i = 0; Symbol[i]; ++i)
    ch2rank[Symbol[i]] = i;
}

void display(const Board &S) {
  int i, j;
  printf("T%03d\n", S.turn);
  printf("  ");
  for (i = 0; i < 8; ++i)
    printf("%d ", i+1);
  puts("");
  for (j = 0; j < 4; ++j, puts("")) {
    printf("%c ", 'a' + j);
    for (i = 0; i < 8; ++i)
      printf("%c ", Symbol[S.board[i*4+j]]);
  }
  printf("r %d p %d h %llu\n", S.rep[S.turn], S.peace[S.turn], S.z);
}

void replay(Board& S, const char m[]) {
  Pos p0 = m[0]-'a' + (m[1]-'1')*4, p1 = m[3]-'a' + (m[4]-'1')*4;
  Rank r = ch2rank[m[3]];
  if (m[2] != '-') {
    p1 = p0;
    if (S.turn == 0 && r%2)
      ++S.turn;
  }
  play(S, p0, p1);
  if (m[2] != '-')
    reveal(S, p0, r);
}

void loadboard(Board& S, const char filename[]) {
  const int BUFLEN = 99;
  FILE *fp = fopen(filename, "r");
  char buf[BUFLEN];
  int i;
  interface_init();
  fgets(buf, BUFLEN, fp);   //date time
  fgets(buf, BUFLEN, fp);   //players
  fgets(buf, BUFLEN, fp);   //piece count
  for (i = 0; i < 8; ++i)
    fgets(buf, BUFLEN, fp); //initial board
  fgets(buf, BUFLEN, fp);   //first player
  fscanf(fp, "%*s %*s %d", &TL);
  TL = TL*1000-1000;
  printf("%d\n", TL);
  while (1) {
    fscanf(fp, "%*s %*s %s", buf);
    if (!buf[1]) break;
    replay(S, buf);
    fscanf(fp, "%s", buf);
    if (!buf[1]) break;
    replay(S, buf);
  }
  fclose(fp);
}
void play(Move m) {
  printf("%c%d %c%d\n", 'a'+m.s%4, 1+m.s/4, 'a'+m.t%4, 1+m.t/4);
  FILE *fp = fopen("move.txt", "w");
  if (m.s == m.t)
    fprintf(fp, "1\n%c%d\n0\n0\n", 'a'+m.s%4, 1+m.s/4);
  else
    fprintf(fp, "0\n%c%d\n%c%d\n0\n", 'a'+m.s%4, 1+m.s/4 , 'a'+m.t%4, 1+m.t/4);
  fclose(fp);  
}
