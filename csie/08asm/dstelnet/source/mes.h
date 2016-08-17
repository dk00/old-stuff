#ifndef MES_H
#define MES_H
#ifdef TW
namespace Mes
{
	const char 
	done[]=			"����",
	fail[]=			"����",
	abort[]=		"���",
	connecting[]=	"�s�u��... ",
	nconnect[]=		"�L�k�s�u  ",
	connected[]=	"�w�s�u    ",
	init_wifi[]=	"Initializing Wifi...",
	found_ap[]=		"\x1b[2;1ffound %d APs\r\n",
	Stat_str[][15]={
		"DISCONNECTED  ",
		"SEARCHING     ",
		"AUTHENTICATING",
		"ASSOCIATING   ",
		"ACQUIRINGDHCP ",
		"ASSOCIATED    ",
		"CANNOTCONNECT "};
}
#else
namespace Mes
{
	const char 
	done[]=			"done",
	fail[]=			"fail",
	abort[]=		"abort",
	connecting[]=	"Connecting... ",
	nconnect[]=		"Can't Connect ",
	connected[]=	"Connected     ",
	init_wifi[]=	"\x1b[1;6f\x1b[2KInitializing Wifi...",
	found_ap[]=		"\x1b[1;1f\x1b[2Kfound %d APs\r\n",
	select_ap[]=	"\x1b[1;10f\x1b[2KSelect an AP\r\n",
	stat_str[][15]={
		"DISCONNECTED  ",
		"SEARCHING     ",
		"AUTHENTICATING",
		"ASSOCIATING   ",
		"ACQUIRINGDHCP ",
		"ASSOCIATED    ",
		"CANNOTCONNECT "};
}
#endif
#include"screen.h"
struct mes{
	char x,buf[64];
	Screen *s;
	mes(Screen &sc,const char *fmt,...);
	~mes();
};
#endif
