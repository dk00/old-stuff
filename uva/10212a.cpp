#include<stdio.h>
main(){
long m,n,p;
while(scanf("%ld %ld",&n,&m)!=EOF){
    for(p=1;m && n%10!=0;m--,n--)p*=n%10;
    while(p%10==0)p/=10;
    for(m=m%40==0?(m>0)*40:m%40;m>=10;m-=10)
        p*=8;
    p%=10;
    for(n=9,m--;m>0;m--,n--)
        p*=n%10;
    while(p%10==0)p/=10;
    printf("%ld\n",p%10);
}
}
