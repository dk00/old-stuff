#include<stdio.h>
#include<string.h>
main(){
char word[10000],c;
int i;
while(scanf("%s%c",word,&c)!=EOF){
    for(i=strlen(word)-1;i>=0;i--)
        printf("%c",word[i]);
    printf("%c",c);
}
}
