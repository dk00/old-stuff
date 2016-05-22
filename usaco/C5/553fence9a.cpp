/*
ID: s0000151
PROG: fence9
LANG: C++
*/
#include<stdio.h>
int gcd(int a,int b){while((a%=b)&&(b%=a));return a+b;}
main(){
freopen("fence9.in","r",stdin);
freopen("fence9.out","w",stdout);
int x,y,w;
scanf("%d %d %d",&x,&y,&w);
printf("%d\n",y?(y*w+2-gcd(x,y)-((x-w)?gcd(y,(w-x)>?(x-w)):y)-w)>>1:0);
}

