#include<stdio.h>
int max(int a,int b){
if(a>b)
	return a;
return b;
}
int min(int a,int b){
if(a<b)
	return a;
return b;
}
void main(){
int i,n,time[10001],start,end,estart=10000,lend=0,mx=-1,mn=0,tx=0,tn=0;
scanf("%d",&n);
for(i=0;i<10000;i++)
	time[i]=0;
for(i=0;i<n;i++){
	scanf("%d %d",&start,&end);
	time[start]+=1;
	time[end]-=1;
	lend=max(end+1,lend);
	estart=min(start,estart);
}
for(i=estart+1;i<=lend;i++)
	time[i]+=time[i-1];
for(i=estart;i<=lend;i++){
	if(time[i]>=1){
		tx++;
		mn=max(tn+1,mn);
		tn=0;
	}
	else if(time[i]==0){
		tn++;
		mx=max(tx-1,mx);
		tx=0;
	}
}
mx=max(tx,mx);
tn=max(tn,mn);
printf("%d %d\n",mx,mn);
scanf("%d");
}