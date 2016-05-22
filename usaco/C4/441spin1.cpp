/*
ID: s0000151
PROG: spin
LANG: C++
*/
#include<stdio.h>
#define INF 2147483647
main(){
freopen("spin.in","r",stdin);
freopen("spin.out","w",stdout);
int i,j,k,t,d,spd,time[360],the[360];
for(k=0;k<360;k++)time[k]=0;
for(i=0;i<5;i++){
    for(k=0;k<360;k++)the[k]=INF;
    scanf("%d %d",&spd,&j);
    while(j--){
        scanf("%d %d",&k,&d);
        for(t=0;t<360;t++){
            k+=spd;k%=360;
            d+=spd;d%=360;
            if(k<=d)
                for(;k<=d;k++)the[k]<?=t;
            else{
                for(;k<360;k++)the[k]<?=t;
                for(k=0;k<=d;k++)the[k]<?=t;
            }
        }
    }
    for(k=0;k<360;k++)time[k]>?=the[k];
}
for(j=INF,k=0;k<360;k++)j<?=time[0];
if(j<=360)printf("%d\n",j);
else puts("none");
}
