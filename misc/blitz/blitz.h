#ifndef BLITZ_H
#define BLITZ_H
enum Dirc {U = 0, L, D, R, X};
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
const int BoardW = 8, BoardH = 8, GridW = 40, GridH = 40;

bool FindGameWindow();
int GetRawBoard(unsigned r[][BoardW*GridW]);
bool Select(int x, int y);
bool SendMove(int x, int y, Dirc d);
void sleep(unsigned t);
#endif
