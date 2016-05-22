#include<stdio.h>
const int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,
67,71,73,79,83,89,97,101};
main(){
int i,j,s,n;
while(scanf("%d",&n) && n){
    printf("%3d! =",n);
    for(j=0;prime[j]<=n;j++){
        for(i=n,s=0;i>=prime[j];s+=(i/=prime[j]));
        printf("%3d",s);
        if(j%15==14 && prime[j+1]<=n){
            puts("");
            printf("      ");
        }
    }
    puts("");
}
}
