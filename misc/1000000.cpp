#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500002
#define MAXN 100000
#define MAXSLOT 100

bool yn[MAXN+1]={0};
//char ans[MAX];
char mem[MAXSLOT+1][MAX];
bool used[MAXSLOT]={0};

class big
{
public:
    int ref;
    char *first;
    void show();
    big(char * in);
    big();
    ~big();
    char * rev(char *a,long len);
    big operator* (big str);
    big operator= (big str);
    big operator+ (big str);
    big operator- (big str);
    int is_smaller(big str);
};

big::big()
{
	int ind=0;
	for(ind=0;ind<MAXSLOT;ind++)
	{
		if(!used[ind])
			break;
	}
	if(ind==MAXSLOT)
		abort();
	first=mem[ind];
	used[ind]=1;
	ref=ind;
	first[0]='\0';
}

big::~big()
{
	used[ref]=0;
}


big::big(char * in)
{
	int ind=0;
	for(ind=0;ind<MAXSLOT;ind++)
	{
		if(!used[ind])
			break;
	}
	if(ind==MAXSLOT)
		abort();
	first=mem[ind];
	used[ind]=1;
	ref=ind;
	strcpy(first,in);
}

int big::is_smaller(big str)
{
	int test;
	long l1=strlen(first);
	long l2=strlen(str.first);
	if(l1>l2)
		return 0;
	else if(l2>l1)
		return 1;
	else
	{
		test=strcmp(first,str.first);
		if(test>=0)
			return 0;
		else
			return 1;
	}

}

char* big::rev(char* a,long len)
{
	long x;char temp;
	for(x=0;x<len/2;x++)
    {temp=a[x];a[x]=a[len-x-1];a[len-x-1]=temp;}
	return a;
}

big big::operator= (big str)
{
	strcpy(first,str.first);
	return *this;
}

big big::operator+ (big str)
{
	char* ans=mem[MAXSLOT];
	long t,l,x,l1,l2;
	l1=strlen(first);
	l2=strlen(str.first);
	rev(first,l1);
	rev(str.first,l2);
	if(l1>l2)
    {
		for(x=l2;x<l1;x++)
			str.first[x]='0';
		str.first[l1]='\0';
		l=l1;
    }
	else
    {
		for(x=l1;x<l2;x++)
			first[x]='0';
		first[l2]='\0';
		l=l2;
    }
	t=0;
	for(x=0;x<l;x++)
    {
		ans[x]=((first[x]-'0'+str.first[x]-'0'+t)%10)+'0';
		t=((first[x]-'0'+str.first[x]-'0'+t)/10);
    }
	ans[l]='\0';
	if(t==1)
    {ans[l]='1';l++;ans[l]='\0';}
	rev(ans,l);
	rev(first,l1);
	rev(str.first,l2);
	return ans;
}

big big::operator* (big str)
{
	char* ans=mem[MAXSLOT];
	long l,l1=strlen(first),l2=strlen(str.first);
	long x,y,t1,i,j,k;
	l=l1+l2-1;
	if(strcmp(first,"0")==0)
		return "0";
	if(strcmp(str.first,"0")==0)
		return "0";
	rev(first,l1);
        if(first!=str.first)
		rev(str.first,l2);
	for(x=0;x<l+1;x++)
		ans[x]='0';
	ans[l+1]='\0';
	for(x=0;x<l1;x++)
    {
		t1=0;
		for(y=0;y<l2;y++)
		{
			i=first[x]-'0';j=str.first[y]-'0';k=ans[x+y]-'0';
			ans[x+y]=( (i*j+t1+k) % 10)+'0';
			t1=(i*j+t1+k) / 10;
		}
		if(t1!=0)
			ans[x+l2]=t1+'0';
    }
	if(t1!=0)
		l++;
	ans[l]='\0';
	rev(ans,l);
	rev(first,l1);
        if(first!=str.first)
	rev(str.first,l2);
	return ans;
}

big now[30],tmp[30];

big big_pow(int x,int y,int depth)
{
	if(y==0)
	{
		now[depth].first[0]='1';
		now[depth].first[1]=0;
		return now[depth];
	}
	tmp[depth]=big_pow(x,y/2,depth+1);
	if(y%2==0)
		return tmp[depth]*tmp[depth];
	else
	{
		sprintf(now[depth].first,"%ld",x);
		return now[depth]*tmp[depth]*tmp[depth];
	}
}

void big::show()
{
	printf("%s\n",first);
}


int test[100000];
int prime[100000];

int main()
{
	big ans;
	int ind=0,i,j,n,t,g,total;
	for(i=2;i<=MAXN;i++)
	{
		if(yn[i])
			continue;
		for(j=2*i;j<=MAXN;j+=i)
			yn[j]=1;
		prime[ind++]=i;
	}
	printf("Please enter a number: \n");
	while(scanf("%d",&n)==1)
	{
		if(n<0)
			break;
		for(i=0;(i<ind && prime[i]<=n);i++)
		{
			t=prime[i];
			g=n;
			total=0;
			while(g!=0)
			{
				g=g/prime[i];
				total+=g;
			}
			test[i]=total;
		}
		ans="1";
		for(i=0;(i<ind && prime[i]<=n);i++)
		{
			ans=ans*big_pow(prime[i],test[i],0);
		}
		ans.show();
	}
	
	return 0;
}
