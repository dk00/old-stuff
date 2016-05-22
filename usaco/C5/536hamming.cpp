/*
ID: s0000151
PROG: hamming
LANG: C++
*/
#include<stdio.h>
int j,k,p,d,dis,list[64];
int check(int num){
	for(j=0;j<p;j++){
		k=(num^list[j]);
		for(dis=0;k>0;k>>=1)dis+=(k&1);
		if(dis<d)return 0;
	}
	return 1;
}
main(){
freopen("hamming.in","r",stdin);
freopen("hamming.out","w",stdout);
int i,n,b;
scanf("%d %d %d",&n,&b,&d);
for(i=0;p<n;i++)if(check(i))list[p++]=i;
printf("%d",list[0]);
for(i=1;i<p;i++)
	printf("%c%d",i%10?' ':'\n',list[i]);
puts("");
}
