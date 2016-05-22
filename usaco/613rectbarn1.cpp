/*
PROG: rectbarn
ID: s0000151
LANG: C++
*/
#include<stdio.h>
char map[3000][3000];
int s1[3000],s2[3000],len[3000];
main(){
int i,j,k,u,r,c,p;
freopen("rectbarn.in","r",stdin);
freopen("rectbarn.out","w",stdout);
scanf("%d %d %d",&r,&c,&p);
while(p--){
    scanf("%d %d",&i,&j);
    map[i-1][j-1]=1;
}
for(i=0;i<r;i++){
    for(j=k=0;j<c;j++){
        ++len[j]*=!map[i][j];
        for(u=0;k>0 && s2[k-1]>len[j];u=1){
            p>?=((j-s1[k-1])*s2[k---1]);
            s2[k]=len[j];
        }
        if(len[j])k+=u;
        if(len[j] && (!k || len[j]>s2[k-1])){
            s1[k]=j;
            s2[k++]=len[j];
        }
    }
    while(k>=0)p>?=((j-s1[k-1])*s2[k---1]);
}
printf("%d\n",p);
}
