#include<stdio.h>
int k,q,d,a[160],f[100000];
bool check(int p){
	int i,j;
	for(i=0;i+d<p;i++){
		for(j=1;j<=d;j++)
			if(f[i+j]!=f[p+j])
				break;
		if(j>d){
			k=i,q=p-i;
			return true;
		}
	}
	return false;
}
int main(){
int i,j,n,m,done;
while(scanf("%d %d %d",&d,&n,&m) && d+n+m){
	for(j=1;j<=d;j++){
		scanf("%d",&a[j]);
		a[j]%=m;
	}
	for(i=1;i<=d;i++){
		scanf("%d",&f[i]);
		f[i]%=m;
	}
	for(done=0;!done;i++){
		for(j=1,f[i]=0;j<=d;j++)
			f[i]=(f[i]+(a[j]*f[i-j])%m)%m;
		done=check(i-d);
	}
	if(n<k)
		printf("%d\n",f[n]);
	else 
		printf("%d\n",f[k+(n-k)%q]);
}
}