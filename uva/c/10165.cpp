#include<stdio.h>
main(){
int n,i,k;
while(scanf("%d",&n) && n){
    k=0;
    while(n--){
        scanf("%d",&i);
        k^=i;
    }
    puts(k?"Yes":"No");
}
}
