#include<stdio.h>
int main(){
long n,i,j;
char x[3]=" x";
/*Find Prime*/
long prime[4793],isP,p;
prime[p=0]=2;prime[++p]=3;
for(i=5;i<=46341;i+=2){
   for(j=1,isP=1;prime[j]*prime[j]<=i;j++){
       if(i%prime[j]==0){
           isP=0;
           break;
       }
   }
   if(isP) prime[++p]=i;
}
while(1){
   scanf("%ld",&n);
   if(n==0) break;
   printf("%ld =",n);
   if(n==1) printf(" 1");
   p=n;
   x[0]='\0';
   if(n<0){printf(" -1");n=-n;x[0]=' ';}
   for(i=0;n>=prime[i]*prime[i] && i<4792;i++){
       if(n%prime[i]==0){
           n/=prime[i];
           printf("%s %d",x,prime[i]);
           x[0]='\0';
           break;
       }
   }
   for(i=0;n>=prime[i]*prime[i] && i<4792;i++){
       while(n%prime[i]==0){
           n/=prime[i];
           printf(" x %d",prime[i]);
       }
   }
   if(p==n)x[0]='\0';
   else x[0]=' ';
   if(n>1) printf("%s %ld",x,n);
   printf("\n");
}
return 0;
}
