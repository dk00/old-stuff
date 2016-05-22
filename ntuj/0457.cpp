#include<cstdio>
#include<algorithm>
#include<math.h>
using namespace std;
const int N=101;
struct ed
{
	int s,t;
	double c;
	ed(){}
	ed(int a,int b,double d){s=a,t=b,c=d;}
	bool operator<(ed a)const{return c<a.c;}
}s[N*N];
int p[N],d[N];
int find(int v)
{
	if(v==p[v])return v;
	return p[v]=find(p[v]);
}
void uni(int a,int b)
{
	a=find(a),b=find(b);
	if(d[a]<d[b])p[a]=b;
	else p[b]=a;
	if(d[a]==d[b])d[a]++;
}
double f(double r,double ax1,double ay1,double ax2,double ay2)
{
	double x1,y1,z1,x2,y2,z2,pi80=acos(-1)/180.0,R=r;
	z1=R*sin(ay1*pi80);
	x1=R*cos(ay1*pi80)*sin(ax1*pi80);
	y1=R*cos(ay1*pi80)*cos(ax1*pi80);
	z2=R*sin(ay2*pi80);
	x2=R*cos(ay2*pi80)*sin(ax2*pi80);
	y2=R*cos(ay2*pi80)*cos(ax2*pi80);
	double d=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));
	return asin(d/r/2)*2*r;
}
double x[N],y[N];
main()
{
	int i,j,k,n,m,T;
	double R,L,D;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lf %lf",&R,&L);
		scanf("%d",&n);
		for(i=0;i<n;i++)
			p[i]=i,d[i]=0;
		for(i=m=0;i<n;i++)
		{
			scanf("%lf %lf",x+i,y+i);
			for(j=0;j<i;j++)
			{
				double D=f(R/2,y[i],x[i],y[j],x[j]);
/*				printf("%lf (%lf %lf) (%lf %lf) => %lf\n",
					R/2,y[i],x[i],y[j],x[j],D);*/
				s[m++]=ed(i,j,D);
			}
		}
		sort(s,s+m);
		for(i=0;i<m;i++)
		{
			s[i].s=find(s[i].s);
			s[i].t=find(s[i].t);
			if(s[i].s!=s[i].t)
			{
				L-=s[i].c;
				uni(s[i].s,s[i].t);
			}
		}
//		printf("%lf\n",L);
		puts((L>=0)?"IS POSSIBLE":"IS NOT POSSIBLE");
	}
}
