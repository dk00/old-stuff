#include<stdio.h>
main(){
int i,j,w,m,n,t,max,min;
while(scanf("%d %d %d",&m,&n,&t)!=EOF){
    min=10000;
    for(i=t/m;i>=0;i--){
        j=(t-i*m)/n;
        w=t-i*m-j*n;
        if(w<min){
            min=w;
            max=i+j;
        }
        else if(w==min && i+j>max)max=i+j;
    }
    printf("%d",max);
    if(min)printf(" %d",min);
    puts("");
}
}
