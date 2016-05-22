/*
ID: s0000151
PROG: clock
LANG: C++
*/

#include<stdio.h>
main(){
freopen("clock.in","r",stdin);
freopen("clock.out","w",stdout);
int hh,mm;
char hr[12][8]={"Twelve","One","Two","Three","Four","Five","Six",
"Seven","Eight","Nine","Ten","Eleven"},
hr2[13][8]={"twelve","one","two","three","four","five","six",
"seven","eight","nine","ten","eleven"},
m1[5][9]={"","Eleven","Twelve","Thirteen","Fourteen"},
m2[6][9]={"","eleven","twelve","thirteen","fourteen","fifteen"},
m3[5][8]={"","","twenty","thirsty","forty"};
scanf("%d:%d",&hh,&mm);
if(!mm)printf("%s o'clock\n",hr[hh%12]);
else if(mm==15)printf("Quarter past %s\n",hr2[hh%12]);
else if(mm==30)printf("%s thirty\n",hr[hh]);
else if(mm==45)printf("Quarter to %s\n",hr2[hh%12+1]);
else if(mm>45)printf("%s to %s\n",(60-mm)>10?
m1[(60-mm)%10]:hr[60-mm],hr2[hh%12+1]);
else{
    printf("%s ",hr[hh]);
    if(mm<=10)printf("%s\n",hr2[mm]);
    else if(mm>=11 && mm <=15)printf("%s\n",m2[mm%10]);
    else if(mm>=16 && mm<=19)printf("%Steen\n",hr2[mm%10]);
    else if(mm>=20 && mm<=45){
        printf("%s",m3[mm/10]);
        if(mm%10)printf("-%s",hr2[mm%10]);
        printf("\n");
    }
}
//scanf(" ");
}
