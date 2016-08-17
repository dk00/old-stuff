#include<math.h>
#include<stdio.h>
int notp[1048577],prime[82025],num[82025],bp[10],bn[10];
main(){
int i,j,p,n,b,bf;
double logn,logb;
prime[0]=2;
for(i=3,p=1;i<1048576;i++,i++){
    if(notp[i])continue;
    for(j=i*3;j<1048576;j+=i*2)notp[j]=1;
    prime[p++]=i;
}
while(scanf("%d %d",&n,&b)!=EOF){
    for(i=0;(prime[i]<=n || prime[i]<=b) && i<82025;i++)num[i]=0;
    for(i=0;prime[i]<=n && i<82025;i++)
        for(j=n,num[i]=0;j>=prime[i];num[i]+=(j/=prime[i]));
    logb=log(b);
    for(i=bf=0;prime[i]<=b;i++)
        if(b%prime[i]==0){
            for(bn[bf]=0;b%prime[i]==0;b/=prime[i],bn[bf]++);
            bp[bf++]=i;
        }
    j=num[bp[0]]/bn[0];
    for(i=1;i<bf;i++)
        j<?=(num[bp[i]]/bn[i]);
    printf("%d ",j);
    for(logn=i=0;prime[i]<=n && i<82025;i++)
        logn+=log(prime[i])*num[i];
    printf("%.0lf\n",floor(logn/logb+1e-10)+1);
}
}
