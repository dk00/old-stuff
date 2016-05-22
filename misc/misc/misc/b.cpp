#include<map>
#include<cstdio>
using namespace std;
const int N=128,M=10240;
int n,m,s[N][N],ub;
char u[M];
inline void go(int a,int b)
{
	int i,j,k,l;
	for(i=j=0;j<n;j++)
	{
		for(k=a;k<=b;k++)
		{
			while(u[s[k][j]]>0)
			{
				for(l=a;l<=b;l++)
					u[s[l][i]]--;
				i++;
			}
			u[s[k][j]]++;
		}
		k=(j-i+1)*(b-a+1);
		if(k>ub)ub=k;
	}
	for(;i<n;i++)
		for(k=a;k<=b;k++)
			u[s[k][i]]=0;
}
main()
{
	int i,j,k,x;
	while(scanf("%d %d",&n,&m)==2)
	{
		map<int,int> h;
		for(i=0,x=1;i<n;i++)
		{
			for(j=0;j<m;j++)
			{
				scanf("%d",&k);
				if(!h[k])
					h[k]=x++;
				s[j][i]=h[k];
			}
		}
		for(i=0;i<M;i++)u[i]=0;
		for(i=ub=0;i<m;i++)
			for(j=i;j<m;j++)
				go(i,j);
		printf("%d\n",ub);
	}
}
