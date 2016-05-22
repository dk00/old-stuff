#include<stdio.h>
#include<time.h>
#define cps CLOCKS_PER_SEC
bool notp[30000000];
int prime[1857859];
main(){
int i,j,p=0,t=2,r=1,n;
time_t st1,st2;;
prime[p++]=2;
scanf("%d",&n);
st1=clock();
for(i=3;i<n;i++,i++){
	if(notp[i])continue;
	for(j=i*3;j<n;j+=(i<<1))notp[j]=1;
	prime[p++]=i;
}
st2=clock();
st2-=st1;
for(i=0;i<30;i++)printf("%4d",prime[i]);
printf("\n%d\n",p);
printf("%lf\n",(double)st2/cps);
scanf(" ");
}
//1857859
