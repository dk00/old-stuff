#include<cstdio>
#include<algorithm>
using namespace std;
const int N=12;
struct tran
{
	int s[N];
	tran &operator*=(const tran &x)
	{
		int tmp[N];
		for(int i=0;i<N;i++)
			tmp[i]=s[x.s[i]];
		for(int i=0;i<N;i++)
			s[i]=tmp[i];
		return *this;
	}
	bool operator<(tran x)const
	{
		for(int i=0;i<N;i++)
			if(s[i]!=x.s[i])return s[i]<x.s[i];
		return 0;
	}
	bool operator!=(tran &x)
	{
		for(int i=0;i<N;i++)
			if(s[i]!=x.s[i])return 1;
		return 0;
	}
	void print()
	{
		int u[N];
		int i,j;
		for(i=0;i<N;i++)
//			printf("%X ",s[i]+1);
			u[i]=1;
		for(i=0;i<N;i++)
			if(u[i])
			{
				printf("(%X",i+1);
				u[i]=0;
				for(j=s[i];u[j];j=s[j])
					printf(" %X",j+1),u[j]=0;
				printf(")");
			}
		puts("");
	}
}t[99];
int n=0;
tran a[3]={
	{{3,0,1,2,7,4,5,6,11,8,9,10}},
	{{5,9,6,1,0,8,10,2,4,11,7,3}},
	{{2,6,10,7,3,1,9,11,0,5,8,4}}
};
int l[]={4,4,4};
void go(int d,tran x)
{
	if(d>=3)
	{
		t[n++]=x;
		return;
	}
	int i=l[d];
	while(i--)
	{
		go(d+1,x);
		x*=a[d];
	}
}
main()
{
	int i;
	tran s;
	for(i=0;i<N;i++)
		s.s[i]=i;
	go(0,s);
	sort(t,t+n);
	for(i=0;i<n;i++)
		if(!i || t[i]!=t[i-1])
			t[i].print();
	printf("%d\n",n);
}
