#include<stdio.h>
#include<string.h>
int num1[251],num2[251],num3[600];
main(){
char s1[251],s2[251];
int i,j,d1,d2;
while(gets(s1)!=NULL && gets(s2)!=NULL){
   d1=strlen(s1);
   d2=strlen(s2);
   
   for(i=d1-1;i>=0;i--)num1[d1-i-1]=s1[i]-'0';
   for(i=d2-1;i>=0;i--)num2[d2-i-1]=s2[i]-'0';
   for(i=d1+d2+1;i>=0;i--)num3[i]=0;
   for(i=0;i<d1;i++)
       for(j=0;j<d2;j++){
           num3[i+j]+=num1[i]*num2[j];
           if(num3[i+j]>=10){
               num3[i+j+1]+=num3[i+j]/10;
               num3[i+j]%=10;
           }
       }
   for(i=d1+d2;!num3[i] && i>0;i--);
   for(;i>=0;i--)printf("%d",num3[i]);
   puts("");
}
}
