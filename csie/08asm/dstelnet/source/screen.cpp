#include<nds.h>
#include<string.h>
#include"text.h"
#include"screen.h"
Screen::Screen(u8 *_adr,u32 *_cx)
{
	cx=_cx;
	adr=_adr;
	hof=0;
	fc=savfc=7;
	top=0;
	bot=Maxn;
	for(int i=0;i<24*80;i++)fcc[i]=7;
}
void Screen::scrollH(int d)
{
	hof+=d<<8;
	if(hof<0)hof=0;
	if(hof>=16384)hof=16383;
	*cx=hof;
}
void Screen::erase(int x1,int y1,int x2,int y2){
	int start_offset=y1*4;
	int len=(y2-y1)*4+4;
	for(int i=x1;i<=x2;++i)
		for(int j=0;j<8;++j)
			memset(adr+start_offset+512*i*8+512*j,0,len);
	start_offset=x1*Maxm+y1;
	len=(x2-x1)*Maxm+(y2-y1)+1;
	memset(buf+start_offset,0,len);
	memset(fcc+start_offset,0,len);
	memset(bcc+start_offset,0,len);
}
/*
void Screen::erase()
{
	erasexy(0,0,24,80);
	x=0;
	y=0;
}
void Screen::erase_line()
{
	erasexy(0,x,0,y);
}
void Screen::erase_before()
{
	memset(adr+512*x*8,0,y*4);
	memset(buf+x*Maxm,' ',y);
}
void Screen::erase_after()
{
	memset(adr+512*x*8+y*4,0,512-y*4);
	memset(buf+x*Maxm+y,' ',80-y);
}
void Screen::erase_up()
{
	memset(adr,0,512*x*8);
}
void Screen::erase_down()
{
}
*/
void Screen::Set_Scroll(int _top,int _bot)
{
	top=_top;
	bot=_bot;
}
void Screen::Scroll_Up()
{
	int start_offset=512*top*8;
	int len=512*(bot-top)*8;
	memcpy(adr+start_offset,adr+start_offset+512*8,len);
	start_offset=top*Maxm;
	len=(bot-top)*Maxm;
	memcpy(buf+start_offset,buf+start_offset+Maxm,len);
	memcpy(fcc+start_offset,fcc+start_offset+Maxm,len);
	memcpy(bcc+start_offset,bcc+start_offset+Maxm,len);
	erase(bot,0,bot,Maxm);
}
void Screen::Scroll_Down()
{
	for(int i=bot-1;i>=top;--i){
		int start_offset=512*i*8;
		int len=512*8;
		memcpy(adr+start_offset+512*8,adr+start_offset,len);
		start_offset=top*Maxm;
		len=(bot-top)*Maxm;
		memcpy(buf+start_offset+Maxm,buf+start_offset,len);
		memcpy(fcc+start_offset+Maxm,fcc+start_offset,len);
		memcpy(bcc+start_offset+Maxm,bcc+start_offset,len);
	}
	erase(top,0,top,Maxm);
}
//Screen Main((u8 *)(0x06000000),(u32 *)&BG3_CX),
Screen Main((u8 *)BG_BMP_RAM(0),(u32 *)&BG3_CX),
	   Sub((u8 *)BG_BMP_RAM_SUB(0),(u32 *)&SUB_BG3_CX);
