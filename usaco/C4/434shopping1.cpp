/*
ID: s0000151
PROG: shopping
LANG: C++
*/
#include<stdio.h>
int dp[6][6][6][6][6],pc[5],pp[5],re[5],of[5],use[1000];
main(){
freopen("shopping.in","r",stdin);
freopen("shopping.out","w",stdout);
int i,j,k,l,m,b,s,yn,on[99],oc[99][5],ok[99][5],op[99];
for(i=0;i<1000;i++)use[i]=-1;
scanf("%d",&s);
for(i=0;i<s;i++){
    scanf("%d",&on[i]);
    for(j=0;j<on[i];j++)
        scanf("%d %d",&oc[i][j],&ok[i][j]);
    scanf("%d",&op[i]);
}
scanf("%d",&b);
for(i=0;i<b;i++){
    scanf("%d %d %d",&pc[i],&re[i],&pp[i]);
    use[pc[i]]=i;
}
for(i=0;i<=5;i++)for(j=0;j<=5;j++)for(k=0;k<=5;k++)for(l=0;l<=5;l++)
    for(m=0;m<=5;m++)
        dp[i][j][k][l][m]=pp[0]*i+pp[1]*j+pp[2]*k+pp[3]*l+pp[4]*m;
while(s--){
    for(yn=1,i=0;i<on[s];i++)
        yn=(yn && use[oc[s][i]]>=0);
    if(!yn)continue;
    for(i=0;i<5;i++)of[i]=0;
    for(i=0;i<on[s];i++)of[use[oc[s][i]]]+=ok[s][i];
    dp[of[0]][of[1]][of[2]][of[3]][of[4]]<?=op[s];
    for(i=0;i<=5;i++)for(j=0;j<=5;j++)for(k=0;k<=5;k++)
    for(l=0;l<=5;l++)for(m=0;m<=5;m++)
        if(dp[i][j][k][l][m] && i+of[0]<=5 && j+of[1]<=5 && k+of[2]<=5
        && l+of[3]<=5 && m+of[4]<=5)
            dp[i+of[0]][j+of[1]][k+of[2]][l+of[3]][m+of[4]]<?=
            dp[i][j][k][l][m]+op[s];
}
printf("%d\n",dp[re[0]][re[1]][re[2]][re[3]][re[4]]);
}
