/* @JUDGE_ID:  58589NF  100  c  "The 3n+1 problem*/
#include<stdio.h>
int main(){
int i,j,max,n,l;
//char line[20];
//gets(line);
while(scanf("%d %d",&i,&j)==2){
    printf("%d %d ",i,j);
    if(i>j){
        max=i;
        i=j;
        j=max;
    }
    for(n=i,max=0;i<=j;i++,n=i){
        for(l=1;n>1;l++){
        if(n%2==1)
            n=3*n+1;
        else
            n/=2;
        }
        if(l>max)
            max=l;
    }
    printf("%ld\n",max);
//    gets(line);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
