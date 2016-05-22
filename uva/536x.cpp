#include<stdio.h>
#include<string.h>
char i,s[30],*post;
void tree(char *in,char *pre){
    if(!*in)return;
    for(i=0;in[i]!=*pre;i++);
    *post--=in[i];
    in[i++]=0;
    tree(in+i,pre+i);
    tree(in,pre+1);
}
main(){
char in[30],pre[30];
while(scanf("%s %s",pre,in)!=EOF){
    *((post=s+strlen(in))--)=0;
    tree(in,pre);
    puts(post+1);
}
}
