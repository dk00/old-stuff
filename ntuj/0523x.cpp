#include<cstdio>
const int N=500001;
void rsort(int x[],int t0[],int t1[],int n,int m)
{
	static int num[N];
	int i;
	for(i=0;i<=m;i++)num[i]=0;
	for(i=0;i<n;i++)num[x[t0[i]]+1]++;
	for(i=1;i<=m;i++)num[i]+=num[i-1];
	for(i=0;i<n;i++)t1[num[x[t0[i]]]++]=t0[i];
}
void sa(char txt[],int t[],int m)
{
	int i,j,n;
	static int s[N*2],tmp[N+2];
	for(n=0;txt[n];n++)s[n]=txt[n],t[n]=n;
	for(i=t[n]=n;i<n*2;i++)s[i]=0;
	for(i=1;i<n;i*=2)
	{
		rsort(s+i,t,tmp,n,m);
		rsort(s,tmp,t,n,m);
		for(j=0;j<n;j++)tmp[j]=s[j];
		for(j=0,m=1;j<n;j++)tmp[j]=s[j];
		for(j=0,m=1;j<n;j++)
		{
			s[t[j]]=m;
			if(tmp[t[j]]!=tmp[t[j+1]] || tmp[t[j]+i]!=tmp[t[j+1]+i])
				m++;
		}
	}
}
int n,s[N],t[N],d[N],x[N];
void go(char s[],int t[],int d[],int n)
{
	int i,j,k;
	for(i=0;i<n;i++)x[t[i]]=i;
	for(i=j=0;i<n;i++)
	{
		if(x[i]==n-1)
		{j=d[x[i]]=0;continue;}
		k=t[x[i]+1];
		while(s[i+j]==s[k+j])
			j++;
		d[x[i]]=j;
		j-=(j>0);
	}
}
char str[N+1];
void Debug()
{
	int i;
	for(i=0;str[i];i++)
		printf("%2d %s\n",d[i],str+t[i]);	
}
int ux=0,tmp[N+1];
int test(int len)
{
	int i,j,k;
	for(i=x[0];i>0 && d[i-1]>=len;i--);
	for(j=x[0];j<n && d[j]>=len;j++);
	for(ux++,k=i;k<=j;k++)
		tmp[t[k]]=ux;
/*	for(i=0;i<n;i++)
		printf("%d ",tmp[i]);
	puts("");*/
	for(i=0;i<n;i+=j)
	{
		for(j=1;j<len;j++)
			if(i+j<n && tmp[i+j]==ux)break;
		if(i+j!=n && tmp[i+j]!=ux)return 0;
	}
	return 1;
}
int pr[N+1],q[N+1];
main()
{
	int i,j,m;
	while(scanf("%s",str)==1)
	{
		sa(str,t,128);
		for(i=0;str[i];i++);
		n=i;
		go(str,t,d,i);
		//Debug();
		/*for(i=0,j=n-1;i<j;)
		{
			k=(i+j)/2;
			if(test(k))j=k-1;
			else i=k+1;
		}*/
		/*for(i=0,j=1;str[j];j++)
		{
			while(i>0 && str[i]!=str[j])i=pr[i-1];
			if(str[i]==str[j])i++;
			pr[j]=i;
		}
		for(i=pr[n-1],m=0;i>0;i=pr[i-1])
			q[m++]=i;
		while(m--)
		{
			if(test(q[m]))
			{
				printf("%d\n",q[m]);
				break;
			}
		}*/
		if(m<0)printf("%d\n",n);
	}
}
