#include<cstdio>
#include"..\\window$.h"
#include"grp.h"
void grpinit()
{
    coninit();
    setcur();
}
const char sx=4,sy=23;
void drawboard(char cl)
{
    int i,j;
    printf(sx,sy,cl,"¢~");
    for(i=0;i<7;i++)
        printf("¢w¢s");
    printf("¢w¢¡");
    printf(sx+1,sy,cl,"¢x");
    for(i=0;i<8;i++)
        printf("  ¢x");
    for(j=1;j<8;j++)
    {
        printf(sx+2*j,sy,cl,"¢u");
        for(i=0;i<7;i++)
            printf("¢w¢q");
        printf("¢w¢t");
        printf(sx+2*j+1,sy,cl,"¢x");
        for(i=0;i<8;i++)
            printf("  ¢x");
    }
    printf(sx+16,sy,cl,"¢¢");
    for(i=0;i<7;i++)
        printf("¢w¢r");
    printf("¢w¢£");
}
char face[][3]={"  ","¡³","¡´","¡¸","¡¹"};
void drawp(char x,char y,char z,char ac,char bg)
{
    int cl=16*bg;
    if(ac)cl|=10;
    else cl|=2;
    printf(sx+1+x*2,sy+2+y*4,cl,face[z]);
}
