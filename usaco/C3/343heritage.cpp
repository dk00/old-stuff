/*
ID: s0000151
PROG: heritage
LANG: C++
*/

#include<stdio.h>
#include<string.h>
#define DEBUG 0
char _post[27],p,i;
void post(char *pre,char *in){
    if(in[0]=='\0')return;
    for(i=0;in[i]!=pre[0];i++);
    _post[p--]=pre[0];
    in[i]='\0';
    post(&pre[i+1],&in[i+1]);
    post(&pre[1],in);
}
main(){
if(!DEBUG){freopen("heritage.in","r",stdin);
freopen("heritage.out","w",stdout);}
char pre[27],in[27];
scanf("%s %s",in,pre);
p=strlen(in);
_post[p--]='\0';
post(pre,in);
puts(_post);
if(DEBUG)scanf(" ");
}
