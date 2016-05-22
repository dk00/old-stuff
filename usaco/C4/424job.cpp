/*
ID: s0000151
PROG: job
LANG: C++
*/
#include<stdio.h>
int rate1[50001],rate2[50001];
main(){
freopen("job.in","r",stdin);
freopen("job.out","w",stdout);
int i,j,t,d,p,n,t1,t2,m1,m2,c1,c2;
scanf("%d %d %d",&n,&m1,&m2);
while(m1--){
    scanf("%d",&c1);
    for(i=1;i<=n*20;i++)rate1[i]+=((i%c1)==0);
}
while(m2--){
    scanf("%d",&c2);
    for(i=1;i<=n*20;i++)rate2[i]+=((i%c2)==0);
}
for(p=t1=0;p<n;p+=rate1[t1])t1++;
for(p=t2=0;p<n;p+=rate2[t2])t2++;
for(p=t=0,d=1;d+t<t1;t++){
    p+=rate1[t+d];
    n-=p;
    if(n<=0)break;
    while(p<rate2[t2-t])
        p+=rate1[t+(++d)];
    p-=rate2[t+d];
}
printf("%d %d\n",t1,t2+d==114?100:t2+d);
}
