#include<stdio.h>
main(){
long long i,j,k,n;
int C=1;
while(scanf("%lld",&n) && n){
    for(i=4,k=1073741825,j=2147483647;i<j;k=(i+j)/2){
        if(k*(k-3)/2==n)break;
        if(k*(k-3)/2<n)i=k+1;
        else j=k;
    }
    printf("Case %d: %d\n",C++,k);
}
}
