/* @JUDGE_ID:  58589NF  579  c++  "ClockHands"*/
#include<stdio.h>
int main(){
long hh,mm;
float rr;
while(1){
    scanf("%d:%d",&hh,&mm);
    if(hh==0 && mm==0)
        break;
    rr=mm*5.5-hh*30;
    rr=rr<0?-rr:rr;
    rr=rr>180?360-rr:rr;
    printf("%-7.3f\n",rr);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
