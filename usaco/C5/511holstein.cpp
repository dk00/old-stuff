/*
ID: s0000151
PROG: holstein
LANG: C++
*/
#include<stdio.h>
int v,g,n,use,best,min,feed,req[25],now[25],vat[15][25];
int check(int d,int tal){
    int i;
    for(i=0;i<v;i++)if(now[i]<req[i])return 0;
    if(d<min || d==min && feed>tal){
        min=d;
        best=use;
        feed=tal;
    }
    return 1;
}
void dfs(int d,int tal,int i){
    if(d>min)return;
    if(check(d,tal))return;
    for(int j;i<g;i++){
        for(j=0;j<v;j++){
            now[j]+=vat[i][j];
            tal+=vat[i][j];
        }
        use|=(1<<i);
        dfs(d+1,tal,i+1);
        use&=~(1<<i);
        for(j=0;j<v;j++){
            now[j]-=vat[i][j];
            tal-=vat[i][j];
        }
    }
}
main(){
freopen("holstein.in","r",stdin);
freopen("holstein.out","w",stdout);
int i,j;
scanf("%d",&v);
for(i=0;i<v;i++)scanf("%d",&req[i]);
scanf("%d",&g);
for(i=0;i<g;i++)
    for(j=0;j<v;j++)scanf("%d",&vat[i][j]);
min=g;feed=2147483647;
dfs(0,0,0);
printf("%d",min);
for(i=0;i<g;i++)if(best&(1<<i))printf(" %d",i+1);
puts("");
}
