#include<stdio.h>
int s[]={1,0,3,0,11,0,41,0,153,0,571,0,2131,0,7953,0,29681,0,110771,0,
413403,0,1542841,0,5757961,0,21489003,0,80198051,0,299303201};
main(){
//s[0]=1,s[2]=3;
//for(i=4;i<31;i++,i++)s[i]=4*s[i-2]-s[i-4];
int i;
while(scanf("%d",&i) && i>=0)printf("%d\n",s[i]);
}
