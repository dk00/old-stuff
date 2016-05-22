#include<nds.h>
#include<cstring>
#include<netdb.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"text.h"
#include"input.h"
#include"keyboard.h"
const int buflen=512;
extern u32 keysPress();
extern int SelectAP();
extern int connect(const char host[],u16 port=23);
extern int run(int sd);
int videoInit()
{
	videoSetMode(MODE_5_2D|DISPLAY_BG3_ACTIVE);	
	videoSetModeSub(MODE_5_2D|DISPLAY_BG3_ACTIVE);
	vramSetMainBanks(VRAM_A_MAIN_BG,VRAM_B_MAIN_BG,VRAM_C_SUB_BG,VRAM_D_LCD);
	BG3_CR=BG_BMP8_512x512;
//	BACKGROUND.control[3] = BG_BMP8_512x256 | BG_MAP_BASE(0);
	BACKGROUND.bg3_rotation.xdy = 0;
	BACKGROUND.bg3_rotation.xdx = 1 << 8;
	BACKGROUND.bg3_rotation.ydx = 0;
	BACKGROUND.bg3_rotation.ydy = 1 << 8;
	SUB_BG3_CR=BG_BMP8_512x512;
	BACKGROUND_SUB.bg3_rotation.xdy = 0;
	BACKGROUND_SUB.bg3_rotation.xdx = 1 << 8;
	BACKGROUND_SUB.bg3_rotation.ydx = 0;
	BACKGROUND_SUB.bg3_rotation.ydy = 1 << 8;
	int i;
	for(i=0;i<32;i++)
		BG_PALETTE[i]=BG_PALETTE[i+32]=
		BG_PALETTE_SUB[i]=BG_PALETTE_SUB[i+32]=
		RGB15((i&1?(15|((i&8)<<1)):0),(i&2?(15|((i&8)<<1)):0),(i&4?(15|((i&8)<<1)):0));
	BG_PALETTE[8]=BG_PALETTE[8+32]=RGB15(10,10,10);
	BG_PALETTE[7]=BG_PALETTE[7+32]=RGB15(20,20,20);
	return 0;
}
int connect_default()
{
	const char host[]="ptt2.cc";
	return connect(host);
}
void subScale(int r)
{
	BACKGROUND_SUB.bg3_rotation.xdx=1<<(8-r);
	BACKGROUND_SUB.bg3_rotation.ydy=1<<(8-r);
}
int main(int argc, char ** argv)
{
	irqInit();
	irqEnable(IRQ_VBLANK);
	lcdMainOnTop();
	videoInit();
	keysSetRepeat(24,12);
	subScale(1);
	if(SelectAP())
	{
		printf(Sub,"\x1b[1;1fCan't connect to AP.\r\n");
		while(1)swiWaitForVBlank();
	}
	printf(Sub,"\x1b[2K\x1b[12;9fWifi is ready.\r\n");
	kb.sc=&Sub;
	kb.display();
	kb.scale(1);
	while(0)
	{
		scanKeys();
		kb.press();
		swiWaitForVBlank();
	}
	//const char *host=kb.getLine();
	while(1)	//Main menu
	{
		printf(Sub,"\x1b[2;2faddress: \x1b[K");
		//int sd=connect_default();
		const char *host=kb.getLine();
		printf(Sub,"\x1b[12;2fConnecting to %s...\x1b[K",host);
		int sd=connect(host);
		if(sd<0)
		{
			printf(Sub,"\x1b[12;2fCan't connect to %s\x1b[K",host);
			scanKeys();
			while(!keysDownRepeat())swiWaitForVBlank();
			continue;
		}
		printf(Sub,"\x1b[12;2fConnected to %s!\x1b[K",host);
		run(sd);
		printf(Sub,"\x1b[12;2fConnection is closed\x1b[K",host);
	}
	while(1)swiWaitForVBlank();
	return 0;
}
