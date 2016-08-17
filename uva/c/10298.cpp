#include<stdio.h>
#include<string.h>
char s[1000001],*ptr;
int n,len[100000];
int check(int p){
    for(ptr=&s[p];*ptr;ptr+=p)
        if(strncmp(ptr,s,p))return 0;
    return 1;
}
main(){
int i,j,k,max;
while(scanf("%s",s) && strcmp(s,".")){
    max=0;
    for(n=0;s[n];n++);
    for(i=1,j=0;i<=n;i++)
        if(n%i==0 && check(i))break;
    printf("%d\n",n/i);
}
}
