/*
ID: s0000151
PROG: milk3
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
int s[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int state[21][21][21],a,b,c;
void dfs(int s1,int s2,int s3){
    if(state[s1][s2][s3])return;
    state[s1][s2][s3]=1;
    if(!s1)s[s3]=1;
    if(s1 && s2<b)dfs(0>?s1+s2-b,b<?s1+s2,s3);
    if(s1 && s3<c)dfs(0>?s1+s3-c,s2,c<?s1+s3);
    if(s2 && s1<a)dfs(a<?s1+s2,0>?s1+s2-a,s3);
    if(s2 && s3<c)dfs(s1,0>?s2+s3-c,c<?s2+s3);
    if(s3 && s1<a)dfs(a<?s1+s3,s2,0>?s1+s3-a);
    if(s3 && s2<b)dfs(s1,b<?s2+s3,0>?s2+s3-b);
}
main(){
if(!DEBUG){freopen("milk3.in","r",stdin);
freopen("milk3.out","w",stdout);}
int i,j,k;
scanf("%d %d %d",&a,&b,&c);
for(i=0;i<=a;i++){
    for(j=0;j<=b;j++){
        for(k=0;k<=c;k++)state[i][j][k]=0;
    }
}
dfs(0,0,c);
for(i=0;i<=c;i++)if(s[i])printf("%d%c",i,i<c?' ':'\n');
if(DEBUG)scanf(" ");
}
