/*
ID: s0000151
PROG: rockers
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
main(){
int i,j,k,l,n,t,m,best=0,s[21],dp[21][21][21];
freopen("rockers.in","r",stdin);
freopen("rockers.out","w",stdout);
scanf("%d %d %d",&n,&t,&m);
for(i=1;i<=n;i++)scanf("%d",&s[i]);
for(i=0;i<m;i++)
    for(j=0;j<=t;j++)
        for(k=0;k<=n;k++){
            for(l=k+1;l<=n;l++)
                if(j+s[l]<=t)
                    dp[i][j+s[l]][l]>?=(dp[i][j][k]+1);
                else
                    dp[i+1][s[l]][l]>?=(dp[i][j][k]+1);
            best>?=dp[i][j][k];
        }
printf("%d\n",best);
}
