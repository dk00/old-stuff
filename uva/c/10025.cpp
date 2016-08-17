#include<stdio.h>
main(){
long long k,n,t;
scanf("%lld",&t);
while(t--){
    scanf("%lld",&k);
    if(k<0)k=-k;
    for(n=1;;n++){
        if(n*(n+1)/2==k)break;
        if(n*(n+1)/2>k && (n*(n+1)/2-k)%2==0)break;
    }
    if(!k)puts("3");
    else printf("%lld\n",n);
    if(t)puts("");
}
}
