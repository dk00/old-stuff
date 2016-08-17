#include<stdio.h>
unsigned long c[20]={1,2,5,14,42,132,429,1430,4862,16796,58786,208012
,742900,2674440,9694845,35357670,129644790,477638700,1767263190};
main(){
    unsigned long n;
    int i;
    while(scanf("%lu",&n)!=EOF){
        for(i=0;n>c[i] && i<20;i++);
        printf("%d\n",i+1);
    }
}
