#ifndef TEXT_H
#define TEXT_H
#include"screen.h"
typedef unsigned short u16;
extern unsigned char font_table[65279][8];
extern void print4(u16 *V,u8 f,u8 b,u16 c);
extern void print(u16 *V,u8 f,u8 b,u16 c);
extern void print(Screen &sc,const char *str);
extern void printf(Screen &sc,const char *fmt,...);
extern void putchar(Screen &sc,char C);
#include"mes.h"
#endif
