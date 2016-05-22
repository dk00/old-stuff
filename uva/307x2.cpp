#include<stdio.h>
#include<stdlib.h>
int numcmp(const void *a,const void *b){
 return *(int *)b-*(int *)a;
}
int y,n,m,max,min,stick[1000],used[1000],able[10000];
void dfs(int len,int d,int i){
   int last=0;
   if(y)return;
   if(!d){
       y=1;
       return;
   }
   if(!len){
       for(i=0;used[i];i++);
       used[i]=1;
       if(stick[i]==m)
           dfs(0,d-1,0);
       else if(stick[i]+min<=m)
           dfs(stick[i],d,i);
       used[i]=0;
       return;
   }
   for(;i<n && !y;i++)
       if(stick[i]!=last && !used[i] && stick[i]+len<=m){
           used[i]=1;
           if(len+stick[i]==m){
               dfs(0,d-1,0);
               used[i]=0;
               return;
           }
           else if(len+stick[i]+min<=m){
               last=stick[i];
               dfs(len+last,d,i);
           }
           used[i]=0;
       }
}
main(){
int i,k,sum;
while(scanf("%d",&n) && n){
 for(i=sum=0;i<n;i++){
     scanf("%d",&stick[i]);
     sum+=stick[i];
 }
 qsort(stick,n,sizeof(stick[0]),numcmp);
 max=stick[0];
 min=stick[n-1];
 for(y=0,i=max;!y && i<=sum/2;i++)
     if(sum%i==0){
         m=i;
         for(k=0;k<=n;k++)used[k]=0;
         dfs(0,sum/i,0);
     }
 printf("%d\n",y?m:sum);
}
}
