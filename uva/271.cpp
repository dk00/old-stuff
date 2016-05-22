#include<stdio.h>
main(){
char c;
int n;
for(n=-1;scanf("%c",&c)!=EOF;n=-1){
    while(c!='\n'){
        if(n==0)n+=500;
        if(c=='N');
        else if(c=='C' || c=='D' || c=='E' || c=='I')n--;
        else n++;
        scanf("%c",&c);
    }
    if(!n)printf("YES\n");
    else printf("NO\n");
}
}
