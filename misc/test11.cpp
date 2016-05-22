#include<stdio.h>
#include<string.h>
main(){
    char line[10000];
    while(gets(line)){
        if(strlen(line)==0)break;
        printf("%ld\n",strlen(line));
    }
}
