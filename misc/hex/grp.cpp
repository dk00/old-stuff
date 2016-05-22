#include"window$.h"
#include"grp.h"
#include<cstdio>
#include<cstring>
void grpinit()
{
    coninit();
    setcur();
}
const int sx=3,sy=21;
void board()
{
    int x=sx;
    color(c_board);
    printf(x++,sy,-1,"        ¢~¢w¢s¢w¢s¢w¢s¢w¢s¢w¢¡");
    printf(x++,sy,-1,"        ¢x  ¢x  ¢x  ¢x  ¢x  ¢x");
    printf(x++,sy,-1,"      ¢~¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢¡");
    printf(x++,sy,-1,"      ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x");
    printf(x++,sy,-1,"    ¢~¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢¡");
    printf(x++,sy,-1,"    ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x");
    printf(x++,sy,-1,"  ¢~¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢¡");
    printf(x++,sy,-1,"  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x");
    printf(x++,sy,-1,"¢~¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢¡");
    printf(x++,sy,-1,"¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x");
    printf(x++,sy,-1,"¢¢¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢£");
    printf(x++,sy,-1,"  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x");
    printf(x++,sy,-1,"  ¢¢¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢£");
    printf(x++,sy,-1,"    ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x");
    printf(x++,sy,-1,"    ¢¢¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢£");
    printf(x++,sy,-1,"      ¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x");
    printf(x++,sy,-1,"      ¢¢¢s¢r¢s¢r¢s¢r¢s¢r¢s¢r¢s¢£");
    printf(x++,sy,-1,"        ¢x  ¢x  ¢x  ¢x  ¢x  ¢x");
    printf(x++,sy,-1,"        ¢¢¢w¢r¢w¢r¢w¢r¢w¢r¢w¢£");
}
const char face[3][3]={"  ","¡´","¡³"};
void unit(int x,int y,int s,char sel)
{
    int c=c_unit;
    if(sel==1)c=c_se1;
    if(sel==2)c=c_se2;
    printf(sx+1+x*2,sy+y*4+10-x*2,c,face[s]);
}
void MesBar(const char s[])
{
    printf(24,(79-strlen(s))/2,2,s);
    waitkey();
    printf(24,(79-strlen(s))/2,0,s);
}
