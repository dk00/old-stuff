#include<stdio.h>
char s[17]={"1111111111111111"};
int n;
void dfs(int d,int i){
	if(!d){
		puts(s);
		return;
	}
	for(;i<n;i++){
		s[i]='0';
		dfs(d-1,i+1);
		s[i]='1';
	}
}
main(){
int t,h;
scanf("%d",&t);
while(t--){
	scanf("%d %d",&n,&h);
	s[n]='\0';
	dfs(n-h,0);
	s[n]='1';
	if(t)puts("");
}
}
