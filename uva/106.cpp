#include<stdio.h>
long gcd(long a,long b){
    if(b==0)return a;
    return gcd(b,a%b);
}
int used[1000001];
main(){
long i,j,p,t,n,pow2[1001],x,y,z;
for(i=0;i<1001;i++)pow2[i]=i*i;
while(scanf("%ld",&n)!=EOF){
    for(i=p=t=0;i<=n;i++)used[i]=0;
    for(i=2;pow2[i]<n;i++){
        for(j=1;j<i && pow2[i]+pow2[j]<=n;j++){
            z=pow2[i]+pow2[j];
            y=pow2[i]-pow2[j];
            x=2*i*j;
            if(gcd(x,y)==1 && gcd(x,z)==1 && gcd(y,z)==1){
                t++;
                for(p=1;p*z<=n;p++)used[p*z]=used[p*y]=used[p*x]=1;
            }
        }
    }
    for(p=n,i=1;i<=n;i++)p-=used[i];
    printf("%ld %ld\n",t,p);
}
}
