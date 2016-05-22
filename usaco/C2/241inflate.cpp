/*
ID: s0000151
PROG: inflate
LANG: C++
*/

#include<stdio.h>
#include<stdlib.h>
#define DEBUG 0
main(){
if(!DEBUG){freopen("inflate.in","r",stdin);
freopen("inflate.out","w",stdout);}
long i,m,n,max[10001],point,time;
scanf("%d %d",&m,&n);
for(i=0;i<=m;i++)max[i]=0;
while(n--){
    scanf("%d %d",&point,&time);
    for(i=0;i<=m;i++){
        if(time+i<=m)
            max[time+i]>?=max[i]+point;
    }
}
printf("%ld\n",max[m]);
if(DEBUG)scanf(" ");
}
