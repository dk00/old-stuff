#include<cstdio>
#include<cstdarg>
#include"mes.h"
#include"text.h"
mes::mes(Screen& sc,const char *fmt,...)
{
	va_list args;
	va_start(args,fmt);
	vsprintf(buf,fmt,args);
	va_end(args);
	x=sc.x;
	print(sc,buf);
}
mes::~mes()
{
	printf(*s,"\x1b[s\x1b[%d;0f\x1b[u",x);
}
