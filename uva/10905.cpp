#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int lencmp(const void *a,const void *b){
    int l1=(strlen((char *)a)<?strlen((char *)b)),
    l2=strncmp((char *)b,(char *)a,l1);
    return l2?l2:strlen((char *)a)-strlen((char *)b);
}
main(){
int i,n;
char s[50][1000];
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)
        scanf("%s",s[i]);
    qsort(s,n,sizeof(s[0]),lencmp);
    for(i=0;i<n;i++)printf("%s",s[i]);
    puts("");
}
}
