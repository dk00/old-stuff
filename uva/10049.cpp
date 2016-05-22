#include<stdio.h>
#include<malloc.h>
main(){
long i,j,*from,start,end,mid,k;
from=(long *)malloc(sizeof(long)*673367);
from[1]=1;from[2]=2;from[3]=4;
for(i=4,k=2,j=6;i<673367;i++){
    from[i]=j;
    if(i>=from[k+1])k++;
    j+=k;
}
while(1){
    scanf("%ld",&k);
    if(k==0) break;
    for(start=0,end=673366;start<end;){
        mid=(start+end)/2;
        if(from[mid]==k) break;
        else if(from[mid]>k)end=mid-1;
        else start=mid+1;
    }
    if(from[mid]>k) mid--;
    if(from[mid]>k) mid--;
    if(from[mid+1]<=k) mid++;
    printf("%d\n",mid);
}
}
