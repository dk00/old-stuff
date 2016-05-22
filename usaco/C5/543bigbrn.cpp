/*
ID: s0000151
PROG: bigbrn
LANG: C++
*/
int map[1000][1000];
#include<stdio.h>
main(){
freopen("bigbrn.in","r",stdin);
freopen("bigbrn.out","w",stdout);
int i,j,n,t,max=1;
scanf("%d %d",&n,&t);
for(i=0;i<n;i++)
    for(j=0;j<n;j++)map[i][j]=1;
while(t--){
    scanf("%d %d",&i,&j);
    map[i-1][j-1]=0;
}
for(i=1;i<n;i++)
    for(j=1;j<n;j++){
        if(!map[i][j])continue;
        map[i][j]+=(map[i-1][j]<?map[i][j-1]<?map[i-1][j-1]);
        max>?=map[i][j];
    }
printf("%d\n",max);
}
