#include<stdio.h>
char c,s[100000];
main(){
int i,max,fr[256];
while(gets(s)){
    for(c='A';c<='z';c++)fr[c]=0;
    for(i=0;s[i];i++)fr[s[i]]++;
    for(max=0,c='A';c<='Z';c++)max>?=fr[c];
    for(c='a';c<='z';c++)max>?=fr[c];
    for(c='A';c<='Z';c++)if(fr[c]==max)putchar(c);
    for(c='a';c<='z';c++)if(fr[c]==max)putchar(c);
    printf(" %d\n",max);
}
}
