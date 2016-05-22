/*
ID: s0000151
PROG: stall4
LANG: C++
*/
#include<stdio.h>
int i,t,sum,mm[402][402],use[402];
int dfs(int p){
    if(use[p])return 0;
    use[p]=1;
    if(p==t)return 1;
    int j;
    for(j=1;j<=t;j++){
        if(mm[p][j]){
            mm[p][j]=0;
            if(dfs(j)){
                mm[j][p]=1;
                return 1;
            }
            mm[p][j]=1;
        }
    }
    return 0;
}
int go(){
    for(i=1;i<=t;i++)use[i]=0;
    for(i=1;i<=t;i++)
        if(mm[0][i] && dfs(i)){
            mm[0][i]=0;
            mm[i][0]=1;
            return 1;
        }
    return 0;
}
main(){
freopen("stall4.in","r",stdin);
freopen("stall4.out","w",stdout);
int j,n,m,s;
scanf("%d %d",&n,&m);
for(i=1;i<=n;i++)mm[0][i]=1;
for(i=1;i<=m;i++)mm[i+n][n+m+1]=1;
for(i=1;i<=n;i++){
    scanf("%d",&s);
    while(s--){
        scanf("%d",&j);
        mm[i][n+j]=1;
    }
}t=n+m+1;use[0]=1;
while(go()){sum++;}
printf("%d\n",sum);
}
