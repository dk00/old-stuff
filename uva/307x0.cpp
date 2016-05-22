#include<stdio.h>
#include<stdlib.h> 
int stick[100000];
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
main(){
long n,i,j,total;
while(scanf("%d",&n)){
    if(!n)break;
    for(i=0;i<n;i++)scanf("%d",&stick[i]);
    qsort((void *)stick,n,sizeof(stick[0]),numcmp);
    
}
}
