#include<cstdio>
const int M=10000000;
void gcd(int a,int b,int &x,int &y)
{
	int a1=1,a2=0,b1=0,b2=1,t,q,na,nb;
	na=nb=1;
	if(a<0)na=-1,a=-a;
	if(b<0)nb=-1,b=-b;
	while(b)
	{
		q=a/b,t=b,b=a%b;
		a=t,t=a2,a2=a1-a2*q;
		a1=t,t=b2,b2=b1-b2*q;
		b1=t;
	}
	x=a1*na;
	y=b1*nb;
}
int gcd(int a,int b)
{
	while((a%=b)&&(b%=a));
	return a+b;
}
main()
{
	int sx,sy,p,q,r,a,b,L,U,an;
	while(scanf("%d %d",&p,&q)==2 && p+q)
	{
		if(!p || !q)
		{
			printf("%d\n",M+1);
			continue;
		}
		r=gcd(p,q);
		a=p/r,b=q/r;
		gcd(a,-b,sx,sy);
		if(sx<0 || sy<0)
			sx+=b,sy+=a;
		U=((M-sx)/b)<?((M-sy)/a);
		L=-((sx/b)<?(sy/a));
		an=U-L+1;
		gcd(b,-a,sx,sy);
		if(sx<0 || sy<0)
			sx+=a,sy+=b;
		U=(((M-sx)/a)<?((M-sy)/b));
		L=-((sx/a)<?(sy/b));
		an+=U-L+1;
		printf("%d\n",an);
	}
}
