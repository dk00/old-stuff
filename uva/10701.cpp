#include<stdio.h>
#include<string.h>
#include<malloc.h>
char *post;
int p,t;
void tree(char *in,char *pre){
    if(in[0]=='\0')return;
    int i;
    for(i=0;in[i]!=pre[0];i++);
    post[p--]=in[i];
    in[i]='\0';
        tree(&in[i+1],&pre[i+1]);
    tree(&in[0],&pre[1]);
}
main(){
char *in_,*pre_;
in_=(char *)malloc(sizeof(char)*60);
pre_=(char *)malloc(sizeof(char)*60);
post=(char *)malloc(sizeof(char)*60);
scanf("%d",&t);
while(t-- && scanf("%d %s %s",&p,pre_,in_)!=EOF){
    post[p--]='\0';
    tree(in_,pre_);
    printf("%s\n",post);
}
}
