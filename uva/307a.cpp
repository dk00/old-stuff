#include<stdio.h>
int y,n,m,min,max,use[51],num[51],able[10000];
void dfs(int len,int d,int i){
   if(y)return;
   if(!d){
       y=1;
       return;
   }
   if(!len){
       while(!use[i])i--;
       use[i]--;
       if(i==m)
           dfs(0,d-1,max);
       else if(i+min<=m)
           dfs(i,d,i);
       use[i]++;
       return;
   }
   for(;i>0 && !y;i--)
       if(use[i] && i+len<=m){
           use[i]--;
           if(len+i==m){
               dfs(0,d-1,max);
               use[i]++;
               return;
           }
           else if(i+min<=m)
               dfs(len+i,d,i);
           use[i]++;
       }
}
main(){
int i,k,sum,stick;
while(scanf("%d",&n) && n){
   for(min=51,max=i=sum=0;i<n;i++){
       scanf("%d",&stick);
       sum+=stick;
       num[stick]++;
       max>?=stick;
       min<?=stick;
   }
   for(y=0,i=max;!y && i<=50;i++)
       if(sum%i==0){
           m=i;
           for(k=1;k<=50;k++)use[k]=num[k];
           dfs(0,sum/i,max);
       }
   printf("%d\n",y?m:sum);
}
}
