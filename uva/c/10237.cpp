#include<stdio.h>
long long sum,s1[31][32],s2[31][32];
main(){
int i,j,n,k;
for(i=0;i<31;i++)s1[i][0]=1;
s1[1][1]=1;
for(i=2;i<31;i++){      //board i*i
    s1[i][1]=s1[i-1][1]+i-(i+1)%2;
    for(j=2;j<=i;j++)
        s1[i][j]=s1[i-1][j-1]*(i-(i+1)%2-j+1)+s1[i-1][j];
}
for(i=0;i<31;i++)s2[i][0]=1;
for(i=2;i<31;i++){
    s2[i][1]=s2[i-1][1]+i-i%2;
    for(j=2;j<=i;j++)
        s2[i][j]=s2[i-1][j-1]*(i-i%2-j+1)+s2[i-1][j];
}
while(scanf("%d %d",&n,&k) && n && k){
    for(sum=i=0;i<=k;i++){
        if(k-i>n || i>n)continue;
        sum+=s1[n][k-i]*s2[n][i];
    }
    printf("%lld\n",sum);
}
}
