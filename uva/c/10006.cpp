#include<stdio.h>
main(){
unsigned n;
while(scanf("%u",&n)){
    if(!n)break;
    switch(n){
        case 561:
        case 1105:
        case 1729:
        case 2465:
        case 2821:
        case 6601:
        case 8911:
        case 10585:
        case 15841:
        case 29341:
        case 41041:
        case 46657:
        case 52633:
        case 62745:
        case 63973:
            printf("The number %u is a Carmichael number.\n",n);
            break;
        default:
            printf("%u is normal.\n",n);
    }
}
}
