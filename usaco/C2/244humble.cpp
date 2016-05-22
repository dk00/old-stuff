/*
ID: s0000151
PROG: humble
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
long hum[100000];
main(){
if(!DEBUG){freopen("humble.in","r",stdin);
freopen("humble.out","w",stdout);}
long i,j,n,k,next[100],p[100],min,max;
scanf("%ld %ld",&k,&n);
for(i=0;i<k;i++){
    scanf("%ld",&p[i]);
    next[i]=0;
}
for(max=hum[0]=i=1;i<=n;i++){
    while(hum[next[0]]*p[0]<=max)next[0]++;
    min=hum[next[0]]*p[0];
    for(j=1;j<k;j++){
        while(hum[next[j]]*p[j]<=max)next[j]++;
        if(min>hum[next[j]]*p[j])min=hum[next[j]]*p[j];
    }
    max=hum[i]=min;
}
printf("%ld\n",hum[n]);
if(DEBUG)scanf(" ");
}
