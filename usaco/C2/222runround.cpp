/*
ID: s0000151
PROG: runround
LANG: C++
*/
#include<stdio.h>
#include<string.h>
int len;
char used[10],re[10],num[10];
int isra()
{
}
int perm(int d)
{
    if(d+1==len && isra())return 1;
    for(int i=num[d];i<10;i++){
        if(!used[i]){
            used[i]=1;
            num[d]=1;
            used[i]=0;
        }
    }
}
main()
{
    //freopen("runround.in","r",stdin);
    //freopen("runround.out","w",stdout);
    char *t;
    int i;
    gets(num);
    for(i=0;i<10;i++)
        used[i]=0;
    for(t=s;t[0]!='\0';t=&t[1])
        used[t[0]-'0']=1;
    len=strlen(num);
    perm(0);
    puts(num);
}
