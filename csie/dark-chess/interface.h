#ifndef _INTERFACE_H
#define _INTERFACE_H
#include"game.h"
const char Symbol[] = " *pPcCnNrRmMgGkK";
extern unsigned TL;
#ifdef _WIN32
#include<windows.h>
#else
#include<ctime>
inline unsigned GetTickCount() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return ts.tv_sec*1000ll + ts.tv_nsec/1000000;
}
#endif
//  ○卒兵包炮馬碼車硨象相士仕將帥
void interface_init();
void display(const Board &S);
void replay(Board& S, const char m[]);
void loadboard(Board& S, const char filename[]);
void play(Move s);

#endif
