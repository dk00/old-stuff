#include<cmath>
#include<cstdio>
struct frac
{
	int a,b;
	bool operator<=(frac x)const
	{
		return  a*1ll*x.b<=x.a*1ll*b;
	}
	bool operator>=(frac x)const
	{
		return  a*1ll*x.b>=x.a*1ll*b;
	}
	frac operator+(frac x)
	{
		return (frac){a+x.a,b+x.b};
	}
	frac& operator+=(frac x)
	{
		a+=x.a;
		b+=x.b;
		return *this;
	}
};

main()
{
	frac i,j,k,l,x,y;
	while(scanf("%d %d %d %d",&x.a,&x.b,&y.a,&y.b)==4)
	{
		i=(frac){0,1};
		j=(frac){1,0};
		k=i+j;
		while(k<=x || k>=y)
		{
			if(k<=x)
			{
				for(l=j;i+l+l<=x;l+=l);
				i+=l;
			}
			else 
			{
				for(l=i;j+l+l>=y;l+=l);
				j+=l;
			}
			k=i+j;
		}
		printf("%d/%d\n",k.a,k.b);
	}
}
