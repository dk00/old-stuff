/*
ID: s0000151
PROG: runround
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int used[10],re[10],len,ptr,run;
long source;
char num[10];
int isra()
{
    for(ptr=0;ptr<len;ptr++)re[ptr]=1;
    for(ptr=run=0;run<len;run++){
        ptr=ptr+num[ptr]-'0';
        if(re[ptr%=len])re[ptr]=0;
        else break;
    }
    if(run==len)return 1;
    return 0;
}
int perm(int d)
{
    if(d==len)return isra();
    for(int i=num[d]-'0';i<10;i++){
        if(!used[i]){
            used[i]=1;
            num[d]=i+'0';
            if(perm(d+1) && atoi(num)>source)return 1;
            used[i]=0;
        }
        num[d]='1';
    }
    return 0;
}
main()
{
    freopen("runround.in","r",stdin);
    freopen("runround.out","w",stdout);
    int i;
    scanf("%s",&num);
    source=atoi(num);
    for(i=0;i<10;i++)used[i]=0;
    len=strlen(num);
    if(!perm(0)){
        num[++len]='\0';
        for(i=len-1;i>=0;i--)num[i]='1';
        perm(0);
    }
    puts(num);
    //scanf(" ");
}
