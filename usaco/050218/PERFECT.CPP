#include<stdio.h>
void main(){
long n[100],p[100],i,j,sum;
for(i=0;1;i++){
	scanf("%ld",&n[i]);
	if(n[i]<=0)
		break;
	sum=1;
	for(j=2;j*j<=n[i];j++){
		if(n[i]%j==0)
			sum+=(j+n[i]/j);
	}
	if(j*j==n[i])
		sum-=j;
	if(sum>n[i])
		p[i]=1;
	else if(sum==n[i])
		p[i]=0;
	else
		p[i]=-1;
	if(n[i]==1 || n[i]==4)
		p[i]=-1;
}
for(j=0;j<i;j++){
	printf("%ld ",n[j]);
	if(p[j]==1)
		printf("ABUNDANT\n");
	else if(p[j]==0)
		printf("PERFECT\n");
	else
		printf("DEFICIENT\n");
}
}