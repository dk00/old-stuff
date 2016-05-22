/* @JUDGE_ID:  58589NF  374  C++  "Big Mod"*/
#include<stdio.h>
long b,p,m,i,n[32],modb2[32];
long dmod(long p1){
for(i=31;p1<n[i];i--);
if(p1>n[i])
    return(modb2[i]*dmod(p1-n[i]))%m;
return modb2[i];
}
int main(){
for(i=1,n[0]=1;i<32;i++)
    n[i]=n[i-1]*2;
while(scanf("%ld %ld %ld",&b,&p,&m)!=EOF){
    if(p==0) b=1;p=1;
    for(i=1,modb2[0]=b%m;i<32;i++)
        modb2[i]=(modb2[i-1]*modb2[i-1])%m;
    printf("%ld\n",dmod(p));
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
