#include<stdio.h>
#include<string.h>
main(){
int i,j,sum,v[26],link[26][26],to[26];
char s[9999];
while(gets(s)!=NULL){
    for(sum=i=0;i<26;i++){
        v[i]=0;
        for(j=0;j<26;j++)link[i][j]=0;
    }
    while(strcmp(s,"deadend")){
        i=s[0]-'a';
        j=s[strlen(s)-1]-'a';
        v[i]++;
        v[j]++;
        link[i][j]=link[j][i]=strlen(s);
        sum+=link[i][j];
        gets(s);
    }
    for(i=0;i<26;i++)if(v[i] && v[i]%2)break;
    if(i>=26){printf("%d\n",sum);continue;}
    for(j=0;j<26;j++)to[j]=link[i][j]+(link[i][j]==0)*32767;
    to[i]=0;
    while(1){
        for(i=0;!to[i];i++);
        for(j=i+1;j<26;j++)if(to[j] && to[j]<to[i])i=j;
        sum+=to[i];
        to[i]=0;
        if(v[i]%2==1)break;
        for(j=0;j<26;j++)if(link[i][j])to[j]<?=link[i][j];
    }
    printf("%d\n",sum);
}
}
