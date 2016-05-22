#include<stdio.h>
main(){
long long p,q,n,ab[32],s;
int i,max;
while(scanf("%I64d %I64d",&p,&q)){
    if(scanf("%I64d",&n)==EOF)break;
    for(max=0,s=n;s>0;s=s>>1,max++);
    ab[0]=p;
    for(i=1;i<n;i++)ab[i]=ab[i-1]*ab[i-1]-q;
}
}
