#include<stdio.h>
main(){
int i,j,k,m,f,q,pi[1000];
char c,t[10002],p[1002];
scanf("%d%c",&f,&c);
while(f--){
   gets(t);
   scanf("%d%c",&q,&c);
   while(q--){
               gets(p);
               pi[0]=j=-1;
               for(i=1;p[i];i++){
                       while(j>=0 && p[j+1]!=p[i])j=pi[j];
                       if(p[j+1]==p[i])j++;
                       pi[i]=j;
                       printf("%d",pi[i]+1);
               }
               puts("");
               m=i-1;
               for(j=-1,i=0;t[i];i++){
                       while(j>=0 && p[j+1]!=t[i])j=pi[j];
                       if(p[j+1]==t[i])j++;
                       printf("%d",j+1);
                       if(j==m)break;
               }
               puts("");
   }
}
}
