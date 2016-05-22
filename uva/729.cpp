#include<stdio.h>
main(){
int n,h,i,j,t,hd,end;
scanf("%d",&t);
for(;t>0;t--){
    scanf("%d %d",&n,&h);
    hd=1;
    for(i=1;i<h;i++){
	   hd<<=1;
       hd=hd|1;
    }
    for(j=n-1;j>=0;j--)
	   printf("%d",(hd&(1<<j))>0?1:0);
    printf("\n");
    
}
}
