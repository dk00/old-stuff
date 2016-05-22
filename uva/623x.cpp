#include<stdio.h>
#define D1 100000
#include<stdlib.h>
#define max 1000 //1000!~=4.02e+2567
main(){
long unsigned *f[max+1];
int n,i,j,d[max+1];
for(i=0;i<=max;i++){
    d[i]=0;
    f[i]=(long unsigned *)malloc(sizeof(long unsigned)*516);
    for(j=0;j<=515;j++)
        f[i][j]=0;
}
f[0][515]=1;d[0]=515;
for(i=1;i<=max;i++){
    for(j=515;j>=d[i-1];j--)
        f[i][j]=f[i-1][j]*i;
    for(d[i]=0;f[i][d[i]]<=0;d[i]++);
    for(j=515;j>=d[i];j--){
        if(f[i][j]>=D1){
		  f[i][j-1]+=f[i][j]/D1;
		  f[i][j]%=D1;
	   }
    }
    if(f[i][d[i]-1]>0) d[i]--;
}
while(scanf("%d",&n)!=EOF){
    printf("%d!\n",n);
    printf("%lu",f[n][d[n]]);
    for(j=d[n]+1;j<=515;j++)
        printf("%05lu",f[n][j]);
    printf("\n");
}
}
