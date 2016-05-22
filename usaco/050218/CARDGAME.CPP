#include<stdio.h>
void main(){
long i,j,n,win=0;
int card1[10000],card2[10000];
scanf("%ld",&n);
for(i=0;i<n;i++)
	scanf("%d",&card1[i]);
for(i=0;i<n;i++)
	scanf("%d",&card2[i]);
for(i=0,j=0;i<n && j<n;){
	for(;card1[i]>card2[j] && j<n;j++){
		win+=n-i;
	}
	for(;card1[i]<=card2[j] && i<n;i++) {}
/*	if(i>=n)
		break;
	else if(j>=n){
		win+=j*(n-i)
	}	*/
}
printf("%ld\n",win);
}
