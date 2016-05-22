#include<stdio.h>
#define B(n) 1<<n
int bo[4096],i,min;
void play(peb,n){
    bo[peb]=0;
    if(peb&B(1) && peb&B(2) && !peb&B(3) &&
    bo[(peb^(B(1)|B(2))|B(3))])
        play((peb^3)|4,n-1);
    for(i=1;i<11;i++){

    }

}
main(){
int n,sum,peb;
char c;
scanf("%d\n",&n);
for(;n>0;n--){
    for(i=0;i<4096;i++) bo[4096]=1;
    peb=0;sum=0;
    for(i=11;i>=0;i--){
        scanf("%c",&c);
        peb|=(c=='o')<<i;
        if(peb&(1<<i)) sum++;
    }
    play(peb,sum);
}
}
