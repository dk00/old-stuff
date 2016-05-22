#include<stdio.h>
main(){
int n,D[11000],C[11000],i;
for(i=0;i<11000;i++)D[i]=C[i]=0;
while(scanf("%d",&n) && n>1)D[n]=1;
while(scanf("%d",&n) && n>1)C[n]=1;
for(i=100;i<11000;i++){
    if(C[i] && !D[i])printf("%d ",i);
}
scanf("%d",&n);
}
