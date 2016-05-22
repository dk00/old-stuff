/* @JUDGE_ID:  58589NF  294  C++  "Divisors"*/
#include<stdio.h>
main(){
long n,i,u,l;
int prime[3370],isP,p,j;
prime[p=0]=2;prime[++p]=3;
for(i=5;i<=31263;i+=2){
    for(j=1,isP=1;prime[j]*prime[j]<=i;j++){
        if(i%prime[j]==0){
            isP=0;
            break;
        }
    }
    if(isP) prime[++p]=i;
}
long maxn,maxf,f,fsum;
scanf("%d",&j);
for(;j>0;j--){
    scanf("%ld %ld",&l,&u);
    maxn=l;
    maxf=1;
    for(i=l;i<=u;i++){
        for(n=i,p=0,fsum=1;n>1 && p<3370;p++){
            for(f=0;n%prime[p]==0;f++,n/=prime[p]);
            if(f>0) fsum*=(f+1);
        }
        if(fsum>maxf){ maxn=i; maxf=fsum; }
    }
    printf(
    "Between %ld and %ld, %ld has a maximum of %ld divisors.",
    l,u,maxn,maxf);
    printf("\n");
}
return 0;
}//31623
/*@END_OF_SOURCE_CODE*/
