#include<nds.h>
#include<cstdio>
#include<cstdarg>
#include"text.h"
#include"escape.h"

void print4(u16* v,u8 f,u8 b,u16 c)
{
	u8 *font=(u8 *)font_table[c];
	u16 i,j,x;
	register u8 y[4];
	for(i=0;i<8;i++)
	{
		x=font[i];
		for(j=0;j<4;j++)
			if((128>>j)&x)y[j]=f;
			else y[j]=b;
		v[0]=((u16 *)y)[0];
		v[1]=((u16 *)y)[1];
		v+=256;
	}
}
void print(u16* v,u8 f,u8 b,u16 c)
{
	u8 *font=(u8 *)font_table[c];
	u16 i,j,x;
	register u8 y[8];
	for(i=0;i<8;i++)
	{
		x=font[i];
		for(j=0;j<8;j++)
			if((128>>j)&x)y[j]=f;
			else y[j]=b;
		v[0]=((u16 *)y)[0];
		v[1]=((u16 *)y)[1];
		v[2]=((u16 *)y)[2];
		v[3]=((u16 *)y)[3];
		v+=256;
	}
}
char buf[24*80];
int ctrl(Screen &sc,const char buf[])
{
	int i,len;
	for(i=0;buf[i];i++)
	{
		sc.esc[sc.m++]=buf[i];
		if(buf[i]==27)sc.esc[0]=27,sc.m=1;
		else if(('0'<=buf[i] && buf[i]<='9') || buf[i]==';' || buf[i]=='[')
			;
		else
		{
			if(buf[i])
				sc.esc[sc.m]=0,sc.m=0;
			break;
		}
	}
	if(sc.m)return i;
	len=i+1,i=1;
	escape(sc,sc.esc);
	return len;
}
#define ADR(sc) (u16 *)(sc.adr+512*sc.x*8+sc.y*4)
void print(Screen &sc,const char *str)
{
	while(*str)
	{
		if(sc.m>0 || *str==27)
			str+=ctrl(sc,str);
		else if(*str==13)
			sc.y=0,str++;
		else if(*str==10)
		{
			if(sc.x+1<sc.bot)sc.x++;
			else sc.Scroll_Up();
			str++;
		}
		else if(*str==8)
		{
			sc.y--;
			if(sc.y<0)sc.y=0;
			str++;
		}
		else if(*str==7)	//TODO: beep!
			str++;
		else if(*str==9)	//TODO: tab
		{
			sc.y&=~7;
			sc.y+=8;
			if(sc.y>Maxm)
				sc.y=Maxm-1;
			str++;
		}
		else if(sc.wch>0)
		{
			sc.wch=(str[0]<<8)+sc.wch;
			if(sc.y+2<=80)
			{	
				print(ADR(sc),sc.fc,sc.bc,sc.wch);
				sc.buf[sc.x*Maxm+sc.y+1]=*str;
			}
			str++;
			sc.y+=2;
			sc.wch=0;
		}
		else if(sc.y>=80)str++;
		else if(*str>127)
		{
			if(sc.y<80)
			{
				sc.fcc[sc.x*Maxm+sc.y]=sc.fc;
				sc.bcc[sc.x*Maxm+sc.y]=sc.bc;
			}
			sc.wch=sc.buf[sc.x*Maxm+sc.y]=*str++;
		}
		else
		{
			if(sc.y+1<=80)
			{
				print4(ADR(sc),sc.fc,sc.bc,*str);
				sc.fcc[sc.x*Maxm+sc.y]=sc.fc;
				sc.bcc[sc.x*Maxm+sc.y]=sc.bc;
				sc.buf[sc.x*Maxm+sc.y++]=*str;
			}
			str++;
		}
//		if(sc.y>79)sc.y=0,sc.x++;
	}
}
void putchar(Screen &sc,char C)
{
	if(sc.y+1<80)
		print4(ADR(sc),sc.fc,sc.bc,C);
	sc.y++;
}
void printf(Screen &sc,const char *fmt,...)
{
	static char buf[512];
	va_list args;
	va_start(args,fmt);
	vsprintf(buf,fmt,args);
	va_end(args);
	print(sc,buf);
}
