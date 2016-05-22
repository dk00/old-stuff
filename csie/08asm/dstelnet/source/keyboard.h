#ifndef KB_H
#define KB_H
struct Keyboard
{
	Screen *sc;
	int n,h,w,ctrl;
	char buf[64];
	char table[80*24];
	void button(u8 x,u8 y,int c,const char label[]);
	void display();
	void hide();
	char press();
	void scale(int r);
	const char *getLine();
};
extern Keyboard kb;
enum Keys{
	BS=8,Enter=13,Esc=27,Up=28,Down=29,Right=30,Left=31,Del=127,Ctrl=254
};
#endif
