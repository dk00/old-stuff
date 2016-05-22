#include<cstdio>
#include<vector>
using namespace std;
const int N=300002;
vector<int> c[N],f[N],r[N],to[N];
int t,p[N];
int go(int v)
{
    if(v==t)
        return 1;
	if(p[v])return 0;
	p[v]=1;
	for(int i=0;i<c[v].size();i++)
		if(f[v][i]-- && go(c[v][i]))
			return ++f[c[v][i]][r[v][i]];
		else f[v][i]++;
	return 0;
}
int flow()
{
    int i,tmp,sum=0;
	for(int j=0;j<2;j++){
		for(i=0;i<=t;i++)p[i]=0;
		for(tmp=i=0;i<c[0].size();i++)
			if(f[0][i]-- && go(c[0][i])){
                f[c[0][i]][r[0][i]]++;
                tmp++;
            }
            else f[0][i]--;
        printf("%d\n",tmp);
		if(tmp<1)return sum;
		sum+=tmp;
		
	}
}
void add(int a,int x,int b)
{
	c[a].push_back(b);
	f[a].push_back(1);
	to[a].push_back(x);
	r[a].push_back(c[b].size());
	c[b].push_back(a);
	f[b].push_back(0);
	to[b].push_back(0);
	r[b].push_back(c[a].size()-1);
}
main()
{
	int i,j,n,m;
	printf("%d\n",sizeof(vector<int>));
	while(scanf("%d %d",&n,&m)==2){
		t=n+m+1;
		for(i=0;i<=t;i++)
			c[i].clear(),f[i].clear(),r[i].clear(),to[i].clear();
		for(i=1;i<=n;i++)
			add(0,0,i);
		for(i=n+1;i<t;i++)
			add(i,0,t);
		while(m--){
			scanf("%d %d",&i,&j);
			add(i,j,n+m+1);
			add(j,i,n+m+1);
		}
		if(flow()!=n){
			puts("NIE");
			continue;
		}
		puts("TAK");
		for(i=1;i<=n;i++){
			for(j=0;f[i][j];j++);
			printf("%d\n",to[i][j]);
		}
	}
}
