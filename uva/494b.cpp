#include<stdio.h>
int main(){
char c;
int n;
while(scanf("%c",&c)!=EOF){
    for(n=0;c!='\n';){
        if((c>='a' && c<='z') || (c>='A' && c<='Z')){
            for(n++;(c>='a' && c<='z') ||
            (c>='A' && c<='Z');scanf("%c",&c));
        }
        scanf("%c",&c);
    }
    printf("%d\n",n);
}
}
