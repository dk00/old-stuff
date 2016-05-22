
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
int i,j,k,an;
char s[20],t[20];
int Val[200];

inline int ABS(int x)
{
  return (x>0?x:0-x);
}

inline void Init(void)
{
  Val['I']=1;
  Val['V']=5;
  Val['X']=10;
  Val['L']=50;
  Val['C']=100;
  Val['D']=500;
  Val['M']=1000;
}

inline int Rome(char *S)
{
  int i,len=strlen(S),sum=0,max=0;
  Init();
  for(i=len-1;i>=0;i--) {
    if(Val[S[i]]>=max) sum+=Val[S[i]];
    else sum-=Val[S[i]];
    max>?=Val[S[i]];
  }
  return sum;
}

main(){
    Init();
    while(scanf("%s",s)&&s[0]!='#'){
        scanf("%s",t);
        an=ABS(Rome(s)-Rome(t));
        if(an/1000==3)printf("MMM");
        else if(an/1000==2)printf("MM");
        else if(an/1000==1)printf("M");
        if((an/100)%10==9)printf("CM");
        else if((an/100)%10==8)printf("DCCC");
        else if((an/100)%10==7)printf("DCC");
        else if((an/100)%10==6)printf("DC");
        else if((an/100)%10==5)printf("D");
        else if((an/100)%10==4)printf("CD");
        else if((an/100)%10==3)printf("CCC");
        else if((an/100)%10==2)printf("CC");
        else if((an/100)%10==1)printf("C");
        if(an/10%10==9)printf("XC");
        if(an/10%10==8)printf("LXXX");
        if(an/10%10==7)printf("LXX");
        if(an/10%10==6)printf("LX");
        if(an/10%10==5)printf("L");
        if(an/10%10==4)printf("XL");
        if(an/10%10==3)printf("XXX");
        if(an/10%10==2)printf("XX");
        if(an/10%10==1)printf("X");
        if(an%10==9)printf("IX");
        else if(an%10==9)printf("IX");
        else if(an%10==8)printf("VIII");
        else if(an%10==7)printf("VII");
        else if(an%10==6)printf("VI");
        else if(an%10==5)printf("V");
        else if(an%10==4)printf("IV");
        else if(an%10==3)printf("III");
        else if(an%10==2)printf("II");
        else if(an%10==1)printf("I");
        if(an==0)printf("ZERO");
        puts("");
    }
}
