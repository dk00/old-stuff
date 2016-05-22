#include<stdio.h>
main()
{
int vt,v0,n;
double chk;
while(scanf("%d %d",&vt,&v0) && (vt || v0))
    {
    if(v0>=vt)
        puts("0");
    else if(vt%(2*v0)!=0 && vt%v0==0)
        puts("0");
    else
        {
        chk=(double)vt/(2*(double)v0),n=chk;
        if(chk-(double)n<=(double)(n+1)-chk)
            printf("%d\n",n);
        else
            printf("%d\n",n+1);
        }
    }
}
