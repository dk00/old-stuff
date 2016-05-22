#include<stdio.h>
long p,yes,num[256],t;
char c;
int dfs(int n){
    int s=2;
    if(scanf("%ld",&t)!=1)return 1;
    while(scanf("%c",&c)==1 && c!='(');
    s-=dfs(n-=t);
    while(scanf("%c",&c)==1 && c!=')');
    while(scanf("%c",&c)==1 && c!='(');
    s-=dfs(n);
    while(scanf("%c",&c)==1 && c!=')');
    if(!s && !n)yes=1;
    return 0;
}
main(){
for(p=0;p<256;p++)num[p]=0;
for(c='0';c<='9';c++)num[c]=1;
while(scanf("%ld",&p)!=EOF){
    yes=0;
    while(scanf("%c",&c)==1 && c!='(');
    dfs(p);
    while(scanf("%c",&c)==1 && c!=')');
    if(yes)puts("yes");
    else puts("no");
}
}
