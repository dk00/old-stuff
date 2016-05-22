#include<stdio.h>
long pn[50],an[50],tempp[50],tempa[50];
void msort(int start, int end){
	if(start>=end)
		return;
	int mid=(start+end)/2;
	int p1=start,p2=mid+1,p=start;
	msort(start,mid);
	msort(mid+1,end);
	while(p<=end){
		if(p1>mid){
			tempp[p]=pn[p2];
			tempa[p++]=an[p2++];
		}
		else if(p2>end){
			tempp[p]=pn[p1];
			tempa[p++]=an[p1++];
		}
		else if(pn[p1]>pn[p2]){
			tempp[p]=pn[p2];
			tempa[p++]=an[p2++];
		}
		else{
			tempp[p]=pn[p1];
			tempa[p++]=an[p1++];
		}
	}
	for(p=start;p<=end;p++){
		pn[p]=tempp[p];
		an[p]=tempa[p];
	}
}
void main(){
long i,n,m,sum=0;
scanf("%ld %ld",&n,&m);
for(i=0;i<m;i++)
	scanf("%ld %ld",&pn[i],&an[i]);
msort(0,m-1);
for(i=0;i<m;i++){
	if(n-an[i]>=0){
		n-=an[i];
		sum+=(an[i]*pn[i]);
	}
	else{
		sum+=(n*pn[i]);
		break;
	}
}
printf("%ld\n",sum);
}
