#include<set>
#include<cstdio>
using namespace std;
int a[100000],u[100000];
main()
{
	int i,j,k,n,m;
	multiset<int> h;
	while(scanf("%d %d",&m,&n)==2)
	{
		h.clear();
		for(i=0;i<m;i++)
			scanf("%d",a+i);
		for(i=0;i<n;i++)
			scanf("%d",u+i);
		set<int>::iterator p;
		for(i=j=0;i<m;i++)
		{
			h.insert(a[i]);
			if(!i)p=h.begin();
			else if(a[i]<*p)p--;
			while(j<n && i+1==u[j])
			{
				if(j++)p++;
				printf("%d\n",*p);
			}
		}
	}
}
