#include<time.h>
#include<stdio.h>
#include<stdlib.h>
main(){
srand(time(NULL));
int i,t,d,n,m;
scanf("%d",&t);
freopen("10870.in","w",stdout);
while(t--){
    d=2+rand()%13;
    n=d/2+rand()%20;
    m=1+rand()%100;
    printf("%d %d %d\n",d,n,m);
    for(i=0;i<d;i++)
        printf("%d ",rand()%m+1);
    puts("");
    for(i=0;i<d;i++)
        printf("%d ",rand()%m+1);
    puts("");
}
puts("0 0 0");
}
