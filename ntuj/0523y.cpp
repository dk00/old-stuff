#include<cstdio>
const int N=500001;
int p[N],t[N];
char s[N];
void Debug()
{
	int i;
	for(i=0;s[i];i++)
		printf("%3c",s[i]);
	puts("");
	for(i=0;s[i];i++)
		printf("%3d",t[i]);
	puts("");
}
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
main()
{
	int i,j;
	while(scanf("%s",s)==1)
	{
		for(i=0,j=1;s[j];j++)
		{
			while(i>0 && s[i]!=s[j])i=t[i-1];
			if(s[i]==s[j])i++;
			t[j]=i;

			p[i]=i,d[i]=0;
		}
		//Debug();
		for(i=1;i<n;i++)
			if(p[i-1]>0)
				uni(i,p[i-1]);
		
	}
}
