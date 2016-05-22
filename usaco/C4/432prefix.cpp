/*
ID: s0000151
PROG: prefix
LANG: C++
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char data[200001],ok[200021];
int cmp(const void *a,const void *b){
    return strlen((char *)b)-strlen((char *)a);
}
main(){
freopen("prefix.in","r",stdin);
freopen("prefix.out","w",stdout);
int i,k,l,pn,max=0,len[200];
char c,p[200][11];
for(pn=0;scanf("%s",p[pn]) && p[pn][0]!='.';pn++);
qsort(p,pn,sizeof(p[0]),cmp);
for(k=0;k<pn;k++)max>?=(len[k]=strlen(p[k]));
for(l=0;(c=getchar())!=EOF;)if(c!='\n')data[l++]=c;
data[l]='\0';
for(k=0;k<pn;k++)
    if(!strncmp(data,p[k],len[k])){
        for(l=len[k];l--;)
            ok[l]=255;
        break;
    }
for(i=1;data[i]&ok[i-1];i++)
    for(k=0;k<pn;k++)
        if(!strncmp(data+i,p[k],len[k]))
            for(l=len[k]+i-1;!ok[l];l--)
                ok[l]=255;
printf("%d\n",ok[i-1]?i:i-1);
}
