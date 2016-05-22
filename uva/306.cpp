#include<stdio.h>
#include<string.h>
int to[201][201],len[201];
main(){
int n,k,i;
char key1[201],key2[201];
for(i=0;i<201;i++)to[i][0]=i;
while(scanf("%d",&n) && n){
    for(i=1;i<=n;i++)scanf("%d",&to[i][1]);
    for(i=1;i<=n;i++){
        for(len[i]=1;to[to[i][len[i]-1]][1]!=i;len[i]++)
            to[i][len[i]]=to[to[i][len[i]-1]][1];
    }
    while(scanf("%d%c",&k,&key1[0]) && k){
        gets(key1);
        for(i=0;i<n;i++)key2[i]=' ';
        for(i=strlen(key1);i<n;i++)key1[i]=' ';
        key1[i]=key2[i]='\0';
        for(i=0;i<n;i++)
            key2[to[i+1][k%len[i+1]]-1]=key1[i];
        puts(key2);
    }
    puts("");
}
}
