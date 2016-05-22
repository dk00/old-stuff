#include<nds.h>
#include"text.h"
#include"input.h"
#include"keyboard.h"
const char 
	k0[]="1235467890",
	k1[]="ABCDEFGHIJKLM",
	k2[]="NOPQRSTUVWXYZ",
	k3[]="abcdefghijklm",
	k4[]="nopqrstuvwxyz",
	k5[]="~`!@#$%^&*()-_+=",
	k6[]="{}[]|\\:;\"\'<>,./?";
void Keyboard::button(u8 x,u8 y,int c,const char label[])
{
	printf(*sc,"\x1b[%d;%df%s",x+1,y,label);
	for(int i=y;i<sc->y;i++)
		table[x*80+i]=c;
}
void Keyboard::display()
{
	printf(*sc,"\x1b[3;6f");
	int i;
	for(i=0;k0[i];i++)
		table[sc->x*80+sc->y]=k0[i],printf(*sc,"%c ",k0[i]);
	for(i=0;i<2;i++)
		table[sc->x*80+sc->y+i]=8;
	printf(*sc,"BS\r\n");
	sc->y+=3;
	for(i=0;k1[i];i++)
		table[sc->x*80+sc->y]=k1[i],printf(*sc,"%c ",k1[i]);
	printf(*sc,"\r\n");
	sc->y+=3;
	for(i=0;k2[i];i++)
		table[sc->x*80+sc->y]=k2[i],printf(*sc,"%c ",k2[i]);
	printf(*sc,"\r\n");
	sc->y+=3;
	for(i=0;k3[i];i++)
		table[sc->x*80+sc->y]=k3[i],printf(*sc,"%c ",k3[i]);
	printf(*sc,"\r\n");
	sc->y+=3;
	for(i=0;k4[i];i++)
		table[sc->x*80+sc->y]=k4[i],printf(*sc,"%c ",k4[i]);
	printf(*sc,"\r\n");
	for(i=0;k5[i];i++)
		table[sc->x*80+sc->y]=k5[i],printf(*sc,"%c ",k5[i]);
	printf(*sc,"\r\n");
	for(i=0;k6[i];i++)
		table[sc->x*80+sc->y]=k6[i],printf(*sc,"%c ",k6[i]);
	printf(*sc,"\r\n");
	h=8,w=4;
	button(9,8,Ctrl,"Ctrl");
	button(9,14,' ',"spc");
	button(9,19,Enter,"Enter");
}
void Keyboard::hide()
{
	//TODO: disable kb
}
char Keyboard::press()
{
	short x=-1,y,z;
	getTouch(x,y);
	if(x<0)return 0;
	x++,y++;
	x/=h,y/=w;
	z=table[x*80+y];
	if(ctrl)
	{
		ctrl=0;
		if(z>='a' && z<='z')
			z-='a'-1;
		else if(z>='A' && z<='Z')
			z-='A'-1;
		else z=0;
	}
	else if(z==Ctrl)
		ctrl=1,z=254;
	//printf(Sub,"\x1b[s\x1b[11;5ftouch %d,%d %d\x1b[K\x1b[u",x,y,z);
	return z;
}
const char *Keyboard::getLine()
{
	char c;
	n=0;
	while(1)
	{
		scanKeys();
		c=press();
		if(c==Enter || keysDown()&KEY_A)
		{
			buf[n]=0;
			return buf;
		}
		else if(c==BS)
		{
			if(n>0)n--,printf(*sc,"\x1b[D \x1b[D");
		}
		else if(c>0)
			printf(*sc,"%c",buf[n++]=c);
		//if(keys!=0)printf(Sub,"\x1b[s\x1b[5;7ftouch %d     \x1b[u",c);
		swiWaitForVBlank();
	}
}
void Keyboard::scale(int r)
{
	h=8<<r;
	w=4<<r;
}
Keyboard kb;
