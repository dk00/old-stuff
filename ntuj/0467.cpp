#include<cmath>
#include<stack>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100;
struct pt{
	int x,y,v,l;
	pt operator-(pt a)const
	{return (pt){x-a.x,y-a.y};}
	int operator*(pt a)const
	{return x*a.y-a.x*y;}
	bool operator<(pt a)const
	{
		if(x!=a.x)return x<a.x;
		return y<a.y;
	}
	bool operator!=(pt a)const
	{
		return x!=a.x || y!=a.y;
	}
	void print()
	{
		printf("%d %d %d\n",x,y,v);
	}
}s[N],x[N],o;
int n,m,an,mini,t[N],a[N],pn,path[N];
double ex;
inline bool cmpx(pt o,pt a,pt b){return (a-o)*(b-o)<0;}
inline bool cmp(pt a,pt b){return (a-o)*(b-o)<0;}
inline double dis(pt a,pt b)
{return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
inline double len(int t[],int n)
{
	int i,j;
	for(i=0;i<n;i++)
		x[i]=s[t[i]];
	o=x[0];
	sort(x,x+n);
	for(i=j=1;i<n;i++)
		if(x[i]!=x[j-1])
			x[j++]=x[i];
	n=j;
	if(n<2)return 0;
	if(n==2)
		return 2*dis(x[0],x[1]);
	sort(x+1,x+n,cmp);
	stack<pt> st;
	st.push(x[0]);
	st.push(x[1]);
	for(i=2;i<n;i++)
	{
		while(st.size()>2)
		{
			pt x0,x1;
			x1=st.top(),st.pop();
			x0=st.top();
			if(cmpx(x0,x1,x[i]))
			{
				st.push(x1);
				break;
			}				
		}
		st.push(x[i]);
	}
	double sum=0;
	pt x0,x1;
	x0=x1=st.top(),st.pop();
	while(st.size())
	{
		sum+=dis(st.top(),x1);
		x1=st.top(),st.pop();
	}
	sum+=dis(x1,x0);
	return sum;
}
inline void go(int i,int v,int l)
{
	if(v>mini)return;
	if(i>=n)
	{
		double tmp=l-len(t,m);
		if(tmp>=0 && (v<mini || (v==mini && pn<an)))
		{
			mini=v;
			an=pn,ex=tmp;
			for(i=0;i<pn;i++)
				a[i]=path[i];
		}
		return;
	}
	t[m++]=i;
	go(i+1,v,l);
	m--;
	path[pn++]=i;
	go(i+1,v+s[i].v,l+s[i].l);
	pn--;

}
main()
{
	int i,C=0;
	while(scanf("%d",&n)>0 && n)
	{
		for(i=0;i<n;i++)
			t[i]=i,
			scanf("%d %d %d %d",&s[i].x,&s[i].y,&s[i].v,&s[i].l);
		an=mini=200000000;
		go(0,0,0);
		if(C)puts("");
		printf("Forest %d\nCut these trees:",++C);
		for(i=0;i<an;i++)
			printf(" %d",a[i]+1);
		printf("\nExtra wood: %.2lf\n",ex);
	}
}
