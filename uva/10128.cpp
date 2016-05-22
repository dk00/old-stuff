#include<stdio.h>
main(){
long long s[14][14],sum,nfact[13];
int i,j,k,p,r,t,n;
for(nfact[0]=i=1;i<13;i++)nfact[i]=nfact[i-1]*i;
for(s[0][0]=i=1;i<14;i++)s[i][0]=0;
for(i=1;i<14;i++){
    for(j=1;j<=i;j++){
        for(s[i][j]=0,k=j-1;k<=i-1;k++){
            s[i][j]+=s[k][j-1]*nfact[i-k-1]*(nfact[i-1]
            /nfact[i-1-k]/nfact[k]);
        }
    }
}
for(scanf("%d",&t);t>0;t--){
    scanf("%d %d %d",&n,&p,&r);
    for(sum=0,i=p-1;n-i>=r;i++)
        sum+=s[i][p-1]*s[n-i-1][r-1];
    printf("%lld\n",sum);
}
}
