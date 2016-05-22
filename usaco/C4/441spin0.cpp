/*
ID: s0000151
PROG: spin
LANG: C++
*/
#include<stdio.h>
#define DEBUG 1
#define D1 wdg[0][(k+dg[0])%360]
#define D2 wdg[1][(k+dg[1])%360]
#define D3 wdg[2][(k+dg[2])%360]
#define D4 wdg[3][(k+dg[3])%360]
#define D5 wdg[4][(k+dg[4])%360]
int mit,dg[5],spd[5],wdg[5][360];
main(){
if(!DEBUG){freopen("spin.in","r",stdin);
freopen("spin.out","w",stdout);}
int i,j,k,t,stt,end,min=2147483647;
for(i=0;i<5;i++){
    scanf("%d %d",&spd[i],&j);
    while(j--){
        scanf("%d %d",&stt,&end);
        end+=stt;
        for(k=stt;k<=end;k++)wdg[i][k%360]=1;
    }
}
for(t=0;;t++){
    for(k=0;k<360;k++)
        if(D1 && D2 && D3 && D4 && D5)mit=1;
    if(mit)break;
    for(i=0;i<5;i++)dg[i]+=spd[i];
}
printf("%d\n",t);
if(DEBUG)scanf(" ");
}
