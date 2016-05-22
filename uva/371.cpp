#include<stdio.h>
int main(){
int i,j,max,n,r,l;
while(scanf("%d %d",&i,&j) && i+j){
    printf("Between %d and %d, ",i,j);
    if(i>j){
        max=i;
        i=j;
        j=max;
    }
    for(n=i,max=0;i<=j;i++,n=i){
        for(l=1;n>1;l++)
            if(n%2==1)n=3*n+1;
            else n/=2;
        if(l-1>max){
            r=i;
            max=l-1;
        }
    }
    printf("%d generates the longest sequence of %d values.\n",r,max);
//    gets(line);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
