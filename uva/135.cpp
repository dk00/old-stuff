#include<stdio.h>
int k,n,s[1000][1000];
main(){
int i,j,p,k,f=0;
while(scanf("%d",&k)!=EOF){
   if(!k)continue;
   n=k*k-k+1;
   for(i=0;i<n;i++)
       for(j=0;j<n;j++)
           s[i][j]=0;
   s[0][0]=1;
   for(i=0;i<k;i++)
       for(j=i*(k-1)+1;j<(i+1)*(k-1)+1;j++)
           s[i][j]=s[j][i]=1;
   for(i=0;i<k-1;i++)
       for(j=0;j<k-1;j++){
           for(p=0;p<k-1;p++)
               s[(i+1)*(k-1)+(p+i*j)%(k-1)+1][(j+1)*(k-1)+p+1]=1;
       }
   for(i=0;i<n;i++){
       for(j=0;j<n;j++)
           if(s[i][j])printf(" %d",j+1);
       puts("");
   }
   if(f)puts("");
   else f=1;
}
}
