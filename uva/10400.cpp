#include<stdio.h>
#include<string.h>
long done[101][65000],s[100];
char e[5]={' ','+','-','*','/'},path[100];
long p,r;
long dfs(long d,long n){
    if(d>=p && n==r)return 1;
        if(d>=p)return 0;
    if(done[d][n+32000])return 0;
    done[d][n+32000]=1;
    if(n+s[d]<=32000 && n+s[d]>=-32000){
        path[d]=e[1];
        if(dfs(d+1,n+s[d]))return 1;
    }
    if(n-s[d]<=32000 && n-s[d]>=-32000){
        path[d]=e[2];
        if(dfs(d+1,n-s[d]))return 1;
    }
    if(n<=32000/s[d] && n>=-32000/s[d]){
        path[d]=e[3];
        if(dfs(d+1,n*s[d]))return 1;
    }
    if(n%s[d]==0 && n/s[d]<=32000 && n/s[d]>=-32000){
        path[d]=e[4];
        if(dfs(d+1,n/s[d]))return 1;
    }
        return 0;
}
main(){
long n,i;
scanf("%ld",&n);
while(n--){
    scanf("%ld",&p);
    for(i=0;i<p;i++)scanf("%ld",&s[i]);
    scanf("%ld",&r);
    for(i=0;i<=100;i++)memset(done[i],0,sizeof(done[i]));
    if(dfs(1,s[0])){
        printf("%ld",s[0]);
        for(i=1;i<p;i++)
            printf("%c%ld",path[i],s[i]);
        printf("=%ld\n",r);
    }
    else puts("NO EXPRESSION");
}
}
