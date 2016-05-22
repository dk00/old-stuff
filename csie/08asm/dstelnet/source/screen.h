#ifndef SCREEN_H
#define SCREEN_H
#include<nds/jtypes.h>
const int Maxn=24,Maxm=80;
const int colors[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
struct Screen
{
	u8 *adr;
	u32 *cx;
	int hof;
	u8 x,y,fc,bc,savx,savy,savfc,savbc,top,bot;
	char buf[24*80];
	u8 fcc[24*80],bcc[24*80];
	u16 wch;
	u8 m;
	char esc[128];
	Screen(u8 *_adr,u32 *_cx);
	void scrollH(int d);
	void Set_Scroll(int top,int bot);
	void Scroll_Up();
	void Scroll_Down();
	void erase(int x1,int y1,int x2,int y2);
};

extern Screen Main,Sub;
#endif
