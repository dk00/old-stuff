#include<cstdio>
const int N=100001;
int n,s[N];
int go(int x,int m)
{
	int i,j;
	for(i=j=0,m--;m>=0 && i<n;i++)
		if((j+=s[i])>x)j=s[i],m--;
	return m<0;
}
main()
{
	int i,j,k,m;
	while(scanf("%d %d",&n,&m)>0)
	{
		for(k=i=j=0;k<n;k++)
			scanf("%d",s+k),i>?=s[k],j+=s[k];
		while(i<j)
			go(k=(i+j)/2,m)?i=k+1:j=k;
		printf("%d\n",j);
	}
}
