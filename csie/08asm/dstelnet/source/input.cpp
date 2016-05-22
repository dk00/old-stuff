#include<nds.h>
u32 keysPress()
{
	static u32 prev=0,frm=0;
	if(frm++%12==0)prev=0;
	u32 keys=~*(volatile short *)0x027FF00C,press;
	keys=((keys&3)<<10)|((keys<<6)&KEY_TOUCH);
	keys|=0x3ff&~REG_KEYINPUT;
	press=keys&~prev;
	prev=keys;
	return press;
}
void getTouch(short &x,short &y)
{
	u32 keys=keysDown();
	if(KEY_TOUCH&keys)
		y=*(volatile short *)0x027FF004,
		x=*(volatile short *)0x027FF006;
	else x=-1;
}
