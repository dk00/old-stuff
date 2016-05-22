#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
using namespace std;
const int N=100001;
vector<int> s[N];
long long an[100001];
int num[100001],back[100001],No,a[100001],qui[100001];
void f(int x,int y){
	int i,n=0,sum=0;
	num[x]=No;
	back[x]=No;
	qui[x]=1;
	No++;
	for(i=0;i<s[x].size();i++){
		if(!num[s[x][i]]){
			f(num[s[x][i]],y);
			back[x]<back[s[x][i]]?:back[x]=back[s[x][i]];
			qui[x]+=qui[num[s[x][i]]];
			a[n++]=qui[num[s[x][i]]];
		}
		else back[x]<num[s[x][i]]?:back[x]=num[s[x][i]];
	}
	printf("%d %d:\n",x,n);
	for(i=0;i<n;i++){
		printf(" %d",a[i]);
		sum+=a[i];
		an[x]+=a[i]*(y-1-a[i]);
	}
	an[x]+=(y-1-sum)*sum;
	puts("");
}
main(){
	int n,m,i,j,k;
	while(scanf("%d %d",&n,&m)!=EOF){
		memset(num,0,sizeof(num));
		No=1;
		for(i=0;i<n;i++)
			s[i].clear();
		for(i=0;i<m;i++){
			scanf("%d %d",&j,&k);
			s[j].push_back(k);
			s[k].push_back(j);
		}
		f(1,n);
		for(i=0;i<n;i++)printf("%lld\n",an[i]+2*n-2);
	}
}
