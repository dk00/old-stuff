#include<math.h>
#include"bigintA03.h"
int use[500001],ans[]={0,0,0,0,0,0,0,0,0,0};
bigint p,r;
main(){
int i,n,count,t;
long long j,k;
char s[500001],tmp[500001];
for(i=1;i<=100000;i++)
    use[(int)floor(i*log10(i))+1]=i;
use[1]=0;
scanf("%d",&t);
while(t--){
    scanf("%s",s);
    n=strlen(s);
    p=s;
    if(n==1 && s[0]=='1'){
        puts("1");
        continue;
    }
    if(!use[n]){
        puts("-1");
        continue;
    }
    i=use[n];
    for(j=1;i--;j=(j*use[n])%10000000000000LL);
    for(i=n-13,k=0;i<n;k=k*10+s[i++]-'0'){
        j+=3;
        j-=3;
    }
    count=0;
    while(j>1 && k>1){
        if(j%10 != k%10)count++;
        j/=10,k/=10;
    }
    if(count>1){
        puts("-1");
        continue;
    }
    if(n>10000){
        printf("%d\n",use[n]);
        continue;
    }
    r=use[n];
    r.d=1;
    p=1;
    p.d=1;
    for(i=1;i<=use[n];i<<=1,r*=r)
        if(i&use[n])p*=r;
    p.tostring(tmp);
    count=0;
    i=n;
    while(i-- && count<=1)
        if(tmp[i]-s[i])count++;
    if(count>1)
        puts("-1");
    else
        printf("%d\n",use[n]);
}
}
