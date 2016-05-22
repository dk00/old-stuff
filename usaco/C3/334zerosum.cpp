/*
ID: s0000151
PROG: zerosum
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
char op[20]={"1 2 3 4 5 6 7 8 9"},c;
int i,sum,n;
long calcu(char *exp){
    for(sum=1;exp[1]==' ';exp=&exp[2])sum=sum*10+exp[2]-'0';
    c=exp[1];
    exp=&exp[2];
    while(c!='\0'){
        for(i=exp[0]-'0';exp[1]==' ';exp=&exp[2])i=i*10+exp[2]-'0';
        if(c=='+')sum+=i;
        else sum-=i;
        c=exp[1];
        exp=&exp[2];
    }
    return sum;
}
void dfs(int d){
    if(d>=n){
        if(calcu(op)==0)puts(op);
        return;
    }
    dfs(d+1);
    op[d*2-1]='+';
    dfs(d+1);
    op[d*2-1]='-';
    dfs(d+1);
    op[d*2-1]=' ';
}
main(){
if(!DEBUG){freopen("zerosum.in","r",stdin);
freopen("zerosum.out","w",stdout);}
scanf("%d",&n);
op[n*2-1]='\0';
dfs(1);
if(DEBUG)scanf(" ");
}
