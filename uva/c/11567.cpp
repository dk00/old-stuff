#include<cstdio>
int M(int x){return (x+30)/30*10;}
int J(int x){return (x+60)/60*15;}
main()
{
	int i,k,n,T,C=1,a,b;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(i=a=b=0;i<n;i++)
		{
			scanf("%d",&k);
			a+=M(k);
			b+=J(k);
		}
		printf("Case %d: ",C++);
		if(a<b)printf("Mile %d\n",a);
		else if(b<a)printf("Juice %d\n",b);
		else printf("Mile Juice %d\n",a);
	}
}
