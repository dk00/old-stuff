/*
ID: s0000151
PROG: fence9
LANG: C++
*/
#include<stdio.h>
#include<math.h>
main(){
freopen("fence9.in","r",stdin);
freopen("fence9.out","w",stdout);
int i,n,m,p,sum=0;
double j,q,rr=1e-6;
scanf("%d %d %d",&n,&m,&p);
for(q=m,i=1;i<n;i++){
    if(q*i/n<rr)continue;
    sum+=(int)floor(q*i/n-rr);
}
if(p>n){
    if(n>0)sum+=m-1;
    for(i=n+1;i<p;i++){
        if(q*(i-n)/(p-n)<rr)break;
        sum+=(int)floor(q*(i-n)/(p-n)-rr);
    }
}
if(p<n)
    for(i=p+1;i<n;i++){
        if(q*(i-p)/(n-p)<rr)continue;
        sum-=(int)floor(q*(i-p)/(n-p));
    }
printf("%d\n",sum);
}
