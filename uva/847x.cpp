#include<stdio.h>
long long n;
inline int winlose1(long long p);
inline int winlose2(long long p);
main(){
while(scanf("%lld",&n)!=EOF)puts(winlose1(1)?"Stan wins.":"Ollie wins.");
}
inline int winlose1(long long p){
   if(p>=n)return 0;
   for(int i=9;i>1;i--)
       if(winlose2(p*i))return 1;
   return 0;
}
inline int winlose2(long long p){
   if(p>=n)return 1;
   for(int i=9;i>1;i--)
       if(!winlose1(p*i))return 0;
   return 1;
}
