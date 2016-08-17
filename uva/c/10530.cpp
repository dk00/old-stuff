#include<stdio.h>
#include<string.h>
main(){
int n,min,max,honest;
char c,s[100];
while(scanf("%d%c",&n,&c) && n){
    honest=1;
    for(min=1,max=10;gets(s) && strcmp(s,"right on");){
        if(strcmp(s,"too high"))min>?=(n+1);
        else max<?=(n-1);
        if(min>max)honest=0;
        scanf("%d%c",&n,&c);
    }
    if(n<min || n>max)honest=0;
    if(honest)puts("Stan may be honest");
    else puts("Stan is dishonest");
}
}
