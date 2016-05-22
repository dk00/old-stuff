/*
ID: s0000151
PROG: friday
LANG: C++
*/

#include<stdio.h>
#define DEBUG 1
main(){
if(!DEBUG){freopen("friday.in","r",stdin);
freopen("friday.out","w",stdout);}
int week[7],yy,mm,dd,ww,end,mlen[13];
mlen[1]=mlen[3]=mlen[5]=mlen[7]=mlen[8]=mlen[10]=mlen[12]=31;
mlen[4]=mlen[6]=mlen[9]=mlen[11]=30;mlen[2]=28;
week[0]=week[1]=week[2]=week[3]=week[4]=week[5]=week[6]=0;
scanf("%d",&end);
for(ww=1,yy=1900,end+=1900;yy<end;yy++){
    if((yy%4==0 && yy%100!=0) || yy%400==0)mlen[2]++;
    for(mm=1;mm<=12;mm++){
        for(dd=1;dd<=mlen[mm];dd++,ww=(ww+1)%7)
            if(dd==13)week[ww]++;
    }
    if((yy%4==0 && yy%100!=0) || yy%400==0)mlen[2]--;
}
printf("%d",week[6]);
for(ww=0;ww<6;ww++)printf(" %d",week[ww]);
puts("");
if(DEBUG)scanf(" ");
}
