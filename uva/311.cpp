/* @JUDGE_ID:  58589NF  311  C++  "Packets"*/
#include<stdio.h>
int main(){
long p1,p2,p3,p4,p5,p6,pack;
while(1){
    scanf("%ld %ld %ld %ld %ld %ld",&p1,&p2,&p3,&p4,&p5,&p6);
    if(p1==0 && p2==0 && p3==0 && p4==0 && p5==0 &&p6==0) break;
    pack=0;
    pack+=(p6+p5+p4+p3/4);  //Put 6*6 & 5*5 & 4*4 & 3*3
    pack+=(p3>0 && p3%4>0)?1:0;
    p1-=(p5*11);    //p5剩餘空間
    p2-=(p4*5);     //p4剩餘空間
    p2-=(p3>0 && p3%4>0)?7-(p3%4)*2:0; //p3剩餘空間
    p1-=(p3>0 && p3%4>0)?8-(p3%4):0;   //1:7 2:6 3:5
    p1+=p2<0?p2*4:0;//p4,p3放入p2後剩餘空間
    pack+=p2>0?p2/9:0;  //p2
    pack+=(p2>0 && p2%9>0)?1:0;
    p1-=(p1>0 && p2%9>0)?(9-(p2%9))*4:0; //p2剩餘
    pack+=p1>0?p1/36:0;   //p1
    pack+=(p1>0 && p1%36>0)?1:0;
    printf("%ld\n",pack);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
