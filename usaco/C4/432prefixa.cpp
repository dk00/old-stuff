/*
ID: s0000151
PROG: prefix
LANG: C++
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char data[200001],ok[200021],p[200][11];
int pn,max,len[200];
int cmp(const void *a,const void *b){
    return strlen((char *)b)-strlen((char *)a);
}
void dfs(int d){
    max>?=d;
    if(!data[d])return;
    int i,b=0,l;
    for(i=0;i<pn && len[i]>b;i++){
        if(!strncmp(data+d,p[i],len[i])){
            for(l=d+len[i];!ok[l] && l-->d;)
                ok[d]=1;
            dfs(d+len[i]);
        }
        for(b=0,l=d;ok[l];l++,b++);
    }
}
main(){
freopen("prefix.in","r",stdin);
freopen("prefix.out","w",stdout);
int i,k,l;
char s[80];
for(pn=0;scanf("%s",p[pn]) && p[pn][0]!='.';pn++);
qsort(p,pn,sizeof(p[0]),cmp);
for(k=0;k<pn;k++)len[k]=strlen(p[k]);
while(scanf("%s",s)!=EOF)strcat(data,s);
dfs(0);
printf("%d\n",max);
}
