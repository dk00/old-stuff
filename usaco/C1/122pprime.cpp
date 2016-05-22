/*
ID: s0000151
PROG: pprime
LANG: C++
*/

#include<stdio.h>
#define e1 1
#define e2 10
#define e3 100
#define e4 1000
#define e5 10000
#define e6 (long)100000
#define e7 (long)1000000
#define e8 (long)10000000
#define PRIME for(p=1,isP=1;prime[p]*prime[p]<=pp;p++){if(pp%prime[p]==0){isP=0;break;}}if(isP)
main(){
long i,j,k,l;
long prime[4793],isP,p;
prime[p=0]=2;prime[++p]=3;
for(i=5;i<=10000;i+=2){
    for(j=1,isP=1;prime[j]*prime[j]<=i;j++){
        if(i%prime[j]==0){
            isP=0;
            break;
        }
    }
    if(isP)prime[++p]=i;
}
long pprime[10280],pp,n;
pprime[0]=3;pprime[1]=5;pprime[2]=7;pprime[n=3]=11;
//pprime len 3
for(i=1;i<=9;i+=2){
    for(j=0;j<=9;j++){
        pp=i*(e3+e1)+j*e2;
        PRIME pprime[++n]=pp;
    }
}
//pprime len 4
for(i=1;i<=9;i+=2){
    for(j=0;j<=9;j++){
        pp=i*(e4+e1)+j*(e2+e3);
        PRIME pprime[++n]=pp;
    }
}
//pprime len 5
for(i=1;i<=9;i+=2){
    for(j=0;j<=9;j++){
        for(k=0;k<=9;k++){
            pp=i*(e5+e1)+j*(e4+e2)+k*e3;
            PRIME pprime[++n]=pp;
        }
    }
}
//pprime len 6
for(i=1;i<=9;i+=2){
    for(j=0;j<=9;j++){
        for(k=0;k<=9;k++){
            pp=i*(e6+e1)+j*(e5+e2)+k*(e4+e3);
            PRIME pprime[++n]=pp;
        }
    }
}
//pprime len7
for(i=1;i<=9;i+=2){
    for(j=0;j<=9;j++){
        for(k=0;k<=9;k++){
            for(l=0;l<=9;l++){
                pp=i*(e7+e1)+j*(e6+e2)+k*(e3+e5)+l*e4;
                PRIME pprime[++n]=pp;
            }
        }
    }
}
//pprime len 8
for(i=1;i<=9;i+=2){
    for(j=0;j<=9;j++){
        for(k=0;k<=9;k++){
            for(l=0;l<=9;l++){
                pp=i*(e8+e1)+j*(e7+e2)+k*(e3+e6)+l*(e4+e5);
                PRIME pprime[++n]=pp;
            }
        }
    }
}
freopen("pprime.in","r",stdin);
freopen("pprime.out","w",stdout);
long a,b;
scanf("%ld %ld",&a,&b);
for(i=0;pprime[i]<a;i++);
for(;pprime[i]<=b && i<=n;i++)printf("%ld\n",pprime[i]);
//scanf(" ");
}
