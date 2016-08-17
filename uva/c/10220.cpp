#include<stdio.h>
#define D1 100000
#include<stdlib.h>//1000!~=4.02e+2567
main(){
long unsigned *f1,*f2,p[1001],*temp,n;
int i,j,d1,d2;
f1=(long unsigned *)malloc(sizeof(long unsigned)*516);
f2=(long unsigned *)malloc(sizeof(long unsigned)*516);
for(j=0;j<=515;j++){
    f1[j]=0;f2[j]=0;
}
f1[515]=1;d1=515;p[0]=1;
for(i=1;i<=1000;i++){
    for(j=515;j>=d1;j--)
        f2[j]=f1[j]*i;
    for(d2=0;f2[d2]<=0;d2++);
    for(j=515;j>=d2;j--){
        if(f2[j]>=D1){
		  f2[j-1]+=f2[j]/D1;
		  f2[j]%=D1;
	   }
    }
    if(f2[d2-1]>0)d2--;
    for(j=d2,p[i]=0;j<=515;j++){
        for(n=f2[j];n>0;n/=10)
            p[i]+=n%10;
    }
    temp=f1;f1=f2;f2=temp;
    n=d1;d1=d2;d2=n;
}
while(scanf("%lu",&n)!=EOF)
    printf("%lu\n",p[n]);
}
