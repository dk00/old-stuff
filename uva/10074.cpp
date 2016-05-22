#include<stdio.h>
#define big(a,b) a>b?a:b
#define oc -31111
s[251][451]
main(){
int i,j,k,max,sum,n,m,best;
for(i=0;i<251;i++)s[i][0]=0;
for(i=0;i<451;i++)s[0][i]=0;
while(1){
   max=0;best=0;
   scanf("%d %d",&m,&n);
   if(!m && !n) break;
   for(i=1;i<=m;i++){
       for(j=1;j<=n;j++){
           scanf("%d",&s[i][j]);
           if(s[i][j]) s[i][j]=-32767;
           else s[i][j]=1;
           s[i][j]+=s[i][j-1];
       }
   }
   best=s[1][1];
   for(i=1;i<=n;i++){
       for(j=i;j<=n;j++){
           sum=0;max=0;
           for(k=1;k<=m;k++){
               if(sum+s[k][j]-s[k][i-1]>0)
                   sum=sum+s[k][j]-s[k][i-1];
               else sum=0;
               max=big(max,sum);
           }
           best=big(max,best);
       }
   }
   printf("%d\n",best);
}
}
