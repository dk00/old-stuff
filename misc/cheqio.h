#define _MSC_VER 1
#include"scrctrl.h"
const _dx=4,_dy=23;

void print(PCHAR s,...)
{
	va_list arg;
	char result[300];
	va_start(arg,s);
	vsprintf(result,s,arg);
	va_end(arg);
	return myPuts(result);
}

void print(int x,int y,PCHAR s,...)
{
    locate(x+_dx,y+_dy);
	va_list arg;
	char result[300];
	va_start(arg,s);
	vsprintf(result,s,arg);
	va_end(arg);
	return myPuts(result);
}

void show()
{
    int i,j;
    print(0,0,"¢~¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢¡");
    print(1,0,"¢x");
    for(i=0;i<8;i++)
        print("%s¢x",sign[map[0][i]]);
    for(i=1;i<8;i++)
    {
        print(i*2,0,"¢u¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢t");
        print(i*2+1,0,"¢x");
        for(j=0;j<8;j++)
            print("%s¢x",sign[map[i][j]]);
    }
    print(17,"¢¢¢w¢r¢w¢r¢w¢r¢w¢r¢w¢r¢w¢r¢w¢r¢w¢£");
}
