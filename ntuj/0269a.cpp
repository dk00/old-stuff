#include<set>
#include<map>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;
char tmp[9999],x[9999];
int n,p[9999];
int go(multiset<string> h[][26],char a[],int n)
{
	int i;
	for(i=1;i<n-1;i++)
		tmp[i]=a[i];
	tmp[i]=0;
//	printf(" %d",h[a[0]-'a'][a[n-1]-'a'].count(tmp+1));
//	printf(" \"%s\"\n",tmp+1);
	if(n>1)sort(tmp+1,tmp+n-1);
	return h[a[0]-'a'][a[n-1]-'a'].count(tmp+1);
}
void print(map<string,string> s,char x[],int i)
{
	if(!i)return;
	x[i]=0;
	if(i-p[i]>1)sort(x+p[i]+1,x+i-1);
	string tmp=s[x+p[i]];
	print(s,x,p[i]);
	printf("%s%c",tmp.c_str(),i==n?'\n':' ');
}
main()
{
	int i,j,k,l,m,T;
	map<string,string> map;
	multiset<string> h[26][26];
	scanf("%d",&T);
	while(T--)
	{
		map.clear();
		for(i=0;i<26;i++)
			for(j=0;j<26;j++)
				h[i][j].clear();
		scanf("%s %d",x,&i);
		while(i--)
		{
			scanf("%s",tmp);
			string t0=tmp;
			for(j=0;tmp[j];j++);
			if(j>1)sort(tmp+1,tmp+j-1);
			k=tmp[0]-'a',l=tmp[j-1]-'a',tmp[j-1]=0;
			h[k][l].insert(tmp+1);
		//	printf("\"%s\" %d\n",tmp+1,h[k][l].count(tmp+1));
			tmp[j-1]=l+'a';
			map[tmp]=t0;
		}
		for(n=0;x[n];n++)p[n]=-1;
		p[n]=-1;
		p[0]=n+1;
		for(i=1;i<=n;i++)
			for(j=0;p[i]!=-2 && j<=i;j++)
				if(p[j]!=-1 &&(k=go(h,x+j,i-j)))
				{
					if(p[i]>-1 || p[j]==-2 || k>1)p[i]=-2;
					else p[i]=j;
				}
//		for(i=0;i<=n;i++)
//			printf("%d ",p[i]);
		if(p[n]==-2)
		{
			puts("ambiguous");
			continue;
		}
		if(p[n]==-1)
		{
			puts("impossible");
			continue;
		}
		print(map,x,n);
	}
}
