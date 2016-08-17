#include<stdio.h>
main(){
int ex,exp,n,i,j,t,key[1000];
while(scanf("%d",&n)!=EOF){
  for(ex=j=0;j<n;j++)scanf("%d",&key[j]);
  for(i=0;i<n;i++){
      for(exp=j=0;j<n-1;j++){
          if(key[j]>key[j+1]){
              exp++;
              key[j]+=key[j+1];
              key[j+1]=key[j]-key[j+1];
              key[j]-=key[j+1];
          }
      }
      if(!exp)break;
      ex+=exp;
  }
  printf("Minimum exchange operations : %d\n",ex);
}
}
