#include<stdio.h>
int n;
int winlose1(int p);
int winlose2(int p);
main(){
while(scanf("%d",&n)!=EOF)puts(winlose1(1)?"Stan wins.":"Ollie wins.");
}
int winlose1(int p){
    if(p>=n)return 0;
    for(int i=9;i>1;i--)
        if(winlose2(p*i))return 1;
    return 0;
}
int winlose2(int p){
    if(p>=n)return 1;
    for(int i=9;i>1;i--)
        if(!winlose1(p*i))return 0;
    return 1;
}
