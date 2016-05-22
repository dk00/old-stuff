#include<stdio.h>
#include<time.h>
#define cps CLOCKS_PER_SEC
bool notp[30000000];
int prime[1857859];
main(){
int i,j,p=0,t=1,r=3,q=2,n;
time_t st1,st2;;
prime[p++]=2;
prime[p++]=3;
prime[p++]=5;
prime[p++]=7;
scanf("%d",&n);
st1=clock();
for(i=11;i<n;i++,i++,t++,r++,q++){
	t-=(t>=3)*3;
 	r-=(r>=5)*5;
 	q-=(q>=7)*7;
	if(notp[i])continue;
	if(t && r && q){
		for(j=i*3;j<n;j+=(i<<1))notp[j]=1;
		prime[p++]=i;
	}
}
st2=clock();
st2-=st1;
for(i=0;prime[i]<=100;i++)printf(",%d",prime[i]);
printf("\n%d\n",p);
printf("%lf\n",(double)st2/cps);
scanf(" ");
}
//1857859
