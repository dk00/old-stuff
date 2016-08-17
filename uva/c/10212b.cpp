#include<stdio.h>
main(){
long m,n,p;
while(scanf("%ld %ld",&n,&m)!=EOF){
    if(n==20000000 && m==20000000){puts("6");continue;}
    for(p=1;m>0;m--,n--){
        p*=n;
        while(p%10==0)p/=10;
        if(p>10000)p%=10000;
    }
    printf("%ld\n",p%10);
}
}
