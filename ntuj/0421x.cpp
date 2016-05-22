#include<cstdio>
const int N=100001;
int s[N];
int go(int x,int m)
{
	int i,j;
	for(i=j=0,m--;m>=0 && i<n;i++)
		if((j+=s[i])>x)j=s[i],m--;
	return m>=0;
}
main()
{
	int i,j,k,a,n,m;
	while(scanf("%d %d",&n,&m)>0)
	{
		for(a=i=j=0;a<n;a++)
			scanf("%d",s+a),i>?=s[i],j+=s[i];
		while(i<=j)
		{
			k=(i+j)/2;
			if(go(k,m))a=k,i=k+1;
			else j=k-1;
		}
		printf("%d\n",a);
	}
}

