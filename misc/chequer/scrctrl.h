#ifndef SCRCTRL_H
#define SCRCTRL_H

/*
Screen Control functions

void locate(x,y);               Locate cursor at line x, column y
void cls();                     Clear screen and move cursor to top left
void myPuts(str);               Show the string at cursor position
void _myPuts(format,...);       Show string like printf
int inkey();                    Handles keystrokes
void PressAnyKey();             Wait for strikes any key
void color(fore,back);          Set current color
void consoleinit();             Initialize(Only in VC)
*/

#if defined(_MSC_VER)  /*for VC*/

#include <windows.h>

enum {C_UNCHANGE=-1,C_BLACK=0,C_BLUE,C_GREEN,C_CYAN,C_RED,C_MAGENTA,
	C_BROWN,C_LIGHTGRAY,C_DARKGRAY,C_LIGHTBLUE,C_LIGHTGREEN,C_LIGHTCYAN,
	C_LIGHTRED,C_LIGHTMAGENTA,C_YELLOW,C_WHITE};

void locate(short x, short y);
void cls();
BOOL myPuts(PCHAR str);
BOOL _myPuts(PCHAR format, ...);
int inkey();
void PressAnyKey();
void color(short forecolor, short backcolor);
void consoleinit();

#elif defined(__GNUC__)  /*for DJGPP*/

#include <conio.h>

#define locate(x,y) gotoxy(y,x)

int inkey();

#elif defined(__TURBOC__)  /*for TC*/

#include <conio.h>

#define locate(x,y) gotoxy(y,x)

int inkey();

#endif  /*#if defined(...)*/

//common place

#define UP 0x148
#define DOWN 0x150
#define LEFT 0x14B
#define RIGHT 0x14D
#define F2 0x13C

bool PressAnyKeyA(int key);

#endif
#if defined(_MSC_VER)  /*for VC*/

#include <stdio.h>
#include <stdarg.h>

HANDLE hStdIn;
HANDLE hConsole;
INPUT_RECORD inputBuffer;
DWORD dwInputEvents;
COORD position;

void locate(short x, short y)
{
	position.X=y;
	position.Y=x;
	SetConsoleCursorPosition(hConsole,position);
}

void fillcolor(WORD forecolor, WORD backcolor)
{
	WORD clr;
	DWORD dwNums;
	if(forecolor==C_UNCHANGE || backcolor==C_UNCHANGE) return;
	clr=((backcolor << 4) | forecolor);
	position.X=position.Y=0;
	FillConsoleOutputAttribute(hConsole,clr,25*80,position,&dwNums);
}

void cls()
{
	COORD coordScreen = { 0, 0 }; /* here's where we'll home the cursor */
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize; /* number of character cells in the current buffer */

	/* get the number of character cells in the current buffer */
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	/* fill the entire screen with blanks */
	FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten);
	/* get the current text attribute */
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	/* now set the buffer's attributes accordingly */
	fillcolor(C_LIGHTGRAY,C_BLACK);
	/* put the cursor at (0, 0) */
	SetConsoleCursorPosition(hConsole, coordScreen);
	return;
}

BOOL myPuts(PCHAR s)
{
	BOOL bSuccess=TRUE;
	DWORD cCharsWritten;
	/* write the string to the console */
	bSuccess = WriteConsole(hConsole, s, strlen(s), &cCharsWritten, NULL);
	return(bSuccess);
}

BOOL _myPuts(PCHAR s, ...)
{
	va_list arg;
	char result[300];
	va_start(arg,s);
	vsprintf(result,s,arg);
	va_end(arg);
	return myPuts(result);
}

#define choose(array) \
{ \
	if(ctrl) return array[2]; \
	if(alt) return array[3]; \
	if(shift) return array[1]; \
	return array[0]; \
}

#define chooseenh(array) \
{ \
	if(enh) \
	{ \
		if(ctrl) return array[6]; \
		if(alt) return array[7]; \
		if(shift) return array[5]; \
		return array[4]; \
	} \
	else \
	{ \
		if(ctrl) return array[2]; \
		if(alt) return array[3]; \
		if(shift) return array[1]; \
		return array[0]; \
	} \
}

int keytable(unsigned short vk, DWORD ctl)
{
	/*							None,	Shift,	Ctrl,	Alt,	Enh,	S-Enh,	C-Enh,	A-Enh*/
	static int bk[4]={			0x008,	0x208,	0x07F,	0x808};
	static int tab[4]={			0x009,	0x10F,	0x194,	0x1A5};
	static int enter[8]={		0x00D,	0x20D,	0x40D,	0x80D,	0x00D,	0x20D,	0x40D,	0x80D};
	static int esc[4]={			0x01B,	0x21B,	0x41B,	0x81B};
	static int space[4]={		0x020,	0x220,	0x420,	0x820};
	static int num[10][4]={{	0x030,	0x029,	0x430,	0x181},	/*0*/
							{	0x031,	0x021,	0x431,	0x178},	/*1*/
							{	0x032,	0x040,	0x432,	0x179},	/*2*/
							{	0x033,	0x023,	0x433,	0x17A},	/*3*/
							{	0x034,	0x024,	0x434,	0x17B},	/*4*/
							{	0x035,	0x025,	0x435,	0x17C},	/*5*/
							{	0x036,	0x05E,	0x436,	0x17D},	/*6*/
							{	0x037,	0x026,	0x437,	0x17E},	/*7*/
							{	0x038,	0x02A,	0x438,	0x17F},	/*8*/
							{	0x039,	0x028,	0x439,	0x180}};/*9*/
	static int alpha[26][4]={{	0x061,	0x041,	0x001,	0x11E},	/*A*/
							{	0x062,	0x042,	0x002,	0x130},	/*B*/
							{	0x063,	0x043,	0x003,	0x12E},	/*C*/
							{	0x064,	0x044,	0x004,	0x120},	/*D*/
							{	0x065,	0x045,	0x005,	0x112},	/*E*/
							{	0x066,	0x046,	0x006,	0x121},	/*F*/
							{	0x067,	0x047,	0x007,	0x122},	/*G*/
							{	0x068,	0x048,	0x008,	0x123},	/*H*/
							{	0x069,	0x049,	0x009,	0x117},	/*I*/
							{	0x06A,	0x04A,	0x00A,	0x124},	/*J*/
							{	0x06B,	0x04B,	0x00B,	0x125},	/*K*/
							{	0x06C,	0x04C,	0x00C,	0x126},	/*L*/
							{	0x06D,	0x04D,	0x00D,	0x132},	/*M*/
							{	0x06E,	0x04E,	0x00E,	0x131},	/*N*/
							{	0x06F,	0x04F,	0x00F,	0x118},	/*O*/
							{	0x070,	0x050,	0x010,	0x119},	/*P*/
							{	0x071,	0x051,	0x011,	0x110},	/*Q*/
							{	0x072,	0x052,	0x012,	0x113},	/*R*/
							{	0x073,	0x053,	0x013,	0x11F},	/*S*/
							{	0x074,	0x054,	0x014,	0x114},	/*T*/
							{	0x075,	0x055,	0x015,	0x116},	/*U*/
							{	0x076,	0x056,	0x016,	0x12F},	/*V*/
							{	0x077,	0x057,	0x017,	0x111},	/*W*/
							{	0x078,	0x058,	0x018,	0x12D},	/*X*/
							{	0x079,	0x059,	0x019,	0x115},	/*Y*/
							{	0x07A,	0x05A,	0x01A,	0x12C}};/*Z*/
	static int func[12][4]={{	0x13B,	0x154,	0x15E,	0x168},	/*F1*/
							{	0x13C,	0x155,	0x15F,	0x169},	/*F2*/
							{	0x13D,	0x156,	0x160,	0x16A},	/*F3*/
							{	0x13E,	0x157,	0x161,	0x16B},	/*F4*/
							{	0x13F,	0x158,	0x162,	0x16C},	/*F5*/
							{	0x140,	0x159,	0x163,	0x16D},	/*F6*/
							{	0x141,	0x15A,	0x164,	0x16E},	/*F7*/
							{	0x142,	0x15B,	0x165,	0x16F},	/*F8*/
							{	0x143,	0x15C,	0x166,	0x170},	/*F9*/
							{	0x144,	0x15D,	0x167,	0x171},	/*F10*/
							{	0x185,	0x187,	0x189,	0x18B},	/*F11*/
							{	0x186,	0x188,	0x18A,	0x18C}};/*F12*/
//	static int padnum[10]={'0','1','2','3','4','5','6','7','8','9'};
	static int pad[10][8]={{	0x149,	0x221,	0x184,	0x821,	0x149,	0x221,	0x184,	0x199},	/*PgUp*/
							{	0x151,	0x222,	0x176,	0x822,	0x151,	0x222,	0x176,	0x1A1},	/*PgDn*/
							{	0x14F,	0x223,	0x175,	0x823,	0x14F,	0x223,	0x175,	0x19F},	/*End*/
							{	0x147,	0x224,	0x177,	0x824,	0x147,	0x224,	0x177,	0x197},	/*Home*/
							{	0x14B,	0x225,	0x173,	0x825,	0x14B,	0x225,	0x173,	0x19B},	/*Left*/
							{	0x148,	0x226,	0x18D,	0x826,	0x148,	0x226,	0x18D,	0x198},	/*Up*/
							{	0x14D,	0x227,	0x174,	0x827,	0x14D,	0x227,	0x174,	0x19D},	/*Right*/
							{	0x150,	0x228,	0x191,	0x828,	0x150,	0x228,	0x191,	0x1A0},	/*Down*/
							{	0x152,	0x22D,	0x192,	0x82D,	0x152,	0x22D,	0x192,	0x1A2},	/*Insert*/
							{	0x153,	0x22E,	0x193,	0x82E,	0x153,	0x22E,	0x193,	0x1A3}};/*Delete*/
	static int padop[4][4]={{	0x02A,	0x26A,	0x196,	0x137},	/* * */
							{	0x02B,	0x26B,	0x190,	0x14E},	/* + */
							{	0x02D,	0x26D,	0x18E,	0x14A},	/* - */
							{	0x02F,	0x26F,	0x195,	0x1A4}};/* / */
	static int punc1[7][4]={{	0x03B,	0x03A,	0x4BA,	0x127},	/* ; 186 */
							{	0x03D,	0x02B,	0x4BB,	0x183},	/* = 187 */
							{	0x02C,	0x03C,	0x4BC,	0x133},	/* , 188 */
							{	0x02D,	0x05F,	0x01F,	0x182},	/* - 189 */
							{	0x02E,	0x03E,	0x4BE,	0x134},	/* . 190 */
							{	0x02F,	0x03F,	0x4BF,	0x135},	/* / 191 */
							{	0x060,	0x07E,	0x4C0,	0x129}};/* ` 192 */
	static int punc2[4][4]={{	0x05B,	0x07B,	0x01B,	0x11A},	/* [ 219 */
							{	0x05C,	0x07C,	0x01C,	0x12B},	/* \ 220 */
							{	0x05D,	0x07D,	0x01D,	0x11B},	/* ] 221 */
							{	0x027,	0x022,	0x4DE,	0x128}};/* ' 222 */
	static int pad5[4]={		0x14C,	0x20C,	0x18F,	0x80C};
	bool ctrl,alt,shift,enh;
	ctrl=((ctl&0xC)!=0);
	alt=((ctl&0x3)!=0);
	shift=((ctl&0x10)!=0);
	enh=((ctl&0x100)!=0);
	if(vk==VK_BACK)
		choose(bk)
	else if(vk==VK_TAB)
		choose(tab)
	else if(vk==VK_RETURN)
		chooseenh(enter)
	else if(vk==VK_ESCAPE)
		choose(esc)
	else if(vk==VK_SPACE)
		choose(space)
	else if(vk>='0' && vk<='9')
		choose(num[vk-'0'])
	else if(vk>='A' && vk<='Z')
		choose(alpha[vk-'A'])
	else if(vk>=VK_F1 && vk<=VK_F12)
		choose(func[vk-VK_F1])
	else if(vk>=VK_NUMPAD0 && vk<=VK_NUMPAD9)
		return vk-VK_NUMPAD0+'0';
	else if(vk>=VK_PRIOR && vk<=VK_DOWN)
		chooseenh(pad[vk-VK_PRIOR])
	else if(vk==VK_INSERT || vk==VK_DELETE)
		chooseenh(pad[vk-VK_INSERT+8])
	else if(vk==VK_MULTIPLY)
		choose(padop[0])
	else if(vk==VK_ADD)
		choose(padop[1])
	else if(vk==VK_SUBTRACT)
		choose(padop[2])
	else if(vk==VK_DIVIDE)
		choose(padop[3])
	else if(vk>=186 && vk<=192)
		choose(punc1[vk-186])
	else if(vk>=219 && vk<=222)
		choose(punc2[vk-219])
	else
	{
		if(shift) return 0x200+vk;
		if(ctrl) return 0x400+vk;
		if(alt) return 0x800+vk;
		return 0x1000+vk;
	}
}

#undef choose
#undef chooseenh

int inkey()
{
	ReadConsoleInput(hStdIn,&inputBuffer,1,&dwInputEvents);
	if(!(inputBuffer.EventType==KEY_EVENT && inputBuffer.Event.KeyEvent.bKeyDown))
	{
		return -1;
	}
	else
	{
		unsigned short vk=inputBuffer.Event.KeyEvent.wVirtualKeyCode;
		DWORD ctl=inputBuffer.Event.KeyEvent.dwControlKeyState;
		if(vk==VK_LBUTTON || vk==VK_RBUTTON || vk==VK_MBUTTON
			|| vk==VK_SHIFT || vk==VK_CONTROL || vk==VK_MENU
			|| vk==VK_CAPITAL || vk==VK_NUMLOCK || vk==VK_SCROLL
			|| vk==VK_SEPARATOR || vk==VK_LWIN || vk==VK_RWIN
			|| vk==VK_APPS || vk==VK_HELP || vk==VK_SELECT
			|| vk==VK_EXECUTE || vk==VK_CANCEL)
		{
			return -1;
		}
		else
		{
			return keytable(vk,ctl);
		}
	}
}

void PressAnyKey()
{
	while(inkey()==-1);
}

void color(short forecolor, short backcolor)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	WORD clr;
	GetConsoleScreenBufferInfo(hConsole,&csbi);
	clr=csbi.wAttributes;
	if(forecolor!=C_UNCHANGE) clr=((clr & (WORD)0xF0) | forecolor);
	if(backcolor!=C_UNCHANGE) clr=((clr & (WORD)0x0F) | (backcolor << 4));
	SetConsoleTextAttribute(hConsole,clr);
}

void color(short color)
{
	WORD clr;
	clr=color;
	SetConsoleTextAttribute(hConsole,clr);
}

void consoleinit()
{
	hStdIn=GetStdHandle(STD_INPUT_HANDLE);
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
}

#elif defined(__GNUC__)  /*for DJGPP*/

int inkey()
{
	int c;
	if(!kbhit()) return -1;
	if((c=getch())!=0) return c;
	return 0x100+getch();
}

#elif defined(__TURBOC__)  /*for TC*/

int inkey()
{
	int c;
	if(!kbhit()) return -1;
	if((c=getch())!=0) return c;
	return 0x100+getch();
}

#endif

bool PressAnyKeyA(int key)
{
	int k;
	while((k=inkey())==-1);
	return (k==key);
}
