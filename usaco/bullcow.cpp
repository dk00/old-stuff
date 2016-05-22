/* 
PROB: bullcow
LANG: C++ 
*/
#include<cstdio>
const int N=100001,M=5000011;
int s[100001];
main()
{
	int i,n,m;
	freopen("bullcow.in","r",stdin);
	freopen("bullcow.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(i=0;i<=m;i++)
		s[i]=i+2;
	for(;i<n;i++)
		s[i]=(s[i-1]+s[i-m-1])%M;
	printf("%d\n",s[n-1]);		
}
