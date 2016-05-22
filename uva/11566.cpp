#include<map>
#include<string>
#include<cstdio>
const int N=18,L=25,S=1<<16;
using namespace std;
struct Comb{
	int p[N];
	int cmp(const Comb &b,int len)
	{
		for(int i=0;i<len;i++)
		{
			if(p[i]<b.p[i])return -1;
			if(p[i]>b.p[i])return 1;
		}
		return 0;
	}
};
int tp[N];
int n;
char tmp[100000];
string Mname[N],Wname[N];
bool c[N][N];
long long W[N][S];
Comb C[N][S];
char _u[N],p0[N],p1[N];
int go(int d,int i=0)
{
	if(d>=n)
	{
		printf("%s %s",Mname[p0[0]].c_str(),Wname[p1[0]].c_str());
		for(d=1;d<n;d++)
			printf(" %s %s",Mname[p0[d]].c_str(),Wname[p1[d]].c_str());
		puts("");
		return 1;
	}
	if(i>=n)return 0;
	for(int j=0;j<n;j++)
		if(c[i][j] && !_u[j])
		{
			_u[j]=1;
			p0[d]=i,p1[d]=j;
			char tmp=go(d+1,i+1);
			_u[j]=0;
			if(tmp)return 1;
		}
	return go(d,i+1);
}

void go()
{
	int i,j,b;
	Comb T;
	for(i=0;i<=n;i++)
		for(b=0;b<tp[n];b++)
			W[i][b]=0;
	W[0][tp[n]-1]=1;
	for(i=0;i<n;i++)
		for(b=0;b<tp[n];b++)
			for(j=0;j<n;j++)
				if((b&tp[j])&& c[i][j])
				{
					if(!W[i+1][b-tp[j]])
					{
						C[i+1][b-tp[j]]=C[i][b];
						C[i+1][b-tp[j]].p[i]=j;
					}
					else
					{
						T=C[i][b];
						T.p[i]=j;
						if(C[i+1][b-tp[j]].cmp(T,i+1)>0)
							C[i+1][b-tp[j]]=T;
					}
					W[i+1][b-tp[j]]+=W[i][b];
				}
	if(W[n][0])
	{
		printf("%lld\n",W[n][0]);
		for(i=0;i<n-1;i++)
			printf("%s %s ",Mname[i].c_str(),Wname[C[n][0].p[i]].c_str());
		printf("%s %s\n",Mname[n-1].c_str(),Wname[C[n][0].p[n-1]].c_str());
	}
	else puts("No Way");
}
int main()
{
	int i,j,m,T,C=1;
	char *ptr;
	for(i=0;i<N;i++)
		tp[i]=1<<i;
	scanf("%d",&T);
	while(T--)
	{
		map<string,int> mh,wh;
		scanf("%d",&n);
		for(i=0;i<n;i++)
			scanf("%s",tmp),Mname[i]=tmp;
		for(i=0;i<n;i++)
			scanf("%s",tmp),Wname[i]=tmp;
		sort(Mname,Mname+n);
		sort(Wname,Wname+n);
		for(i=0;i<n;i++)
			mh[Mname[i]]=wh[Wname[i]]=i;
		gets(tmp);
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				c[i][j]=0;
		for(i=0;i<n;i++)
		{
			gets(tmp);
			ptr=strtok(tmp," ");
			sscanf(ptr,"%s",tmp);
			tmp[strlen(tmp)-1]=0;
			int i=mh[tmp];
			while(ptr=strtok(NULL," "))
			{
				sscanf(ptr,"%s",tmp);
				c[i][wh[tmp]]=1;
			}
		}
		printf("Case %d:\n",C++);
		go();
	}
}
