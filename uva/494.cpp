/* @JUDGE_ID:  58589NF  494  C++  "Kindergarten Counting Game"*/
#include<stdio.h>
int main(){
char line[1000];
int i,n;
while(gets(line)!=NULL){
    for(i=0,n=0;line[i]!='\0';i++){
        if((line[i]>='a' && line[i]<='z') ||
        (line[i]>='A' && line[i]<='Z')){
            for(n++;(line[i]>='a' && line[i]<='z') ||
            (line[i]>='A' && line[i]<='Z');i++);
        }
    }
    printf("%d\n",n);
}
}
/*@END_OF_SOURCE_CODE*/
