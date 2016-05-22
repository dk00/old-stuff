#include<cstdio>
int n,s1[1000001],s2[1000001],s3[1000001];
void calc(int st,int ed)
{
    if(st>ed)return;
    int mid=(st+ed)/2;
    s2[mid]=(mid-st+1);
    calc(st,mid-1);
    calc(mid+1,ed);
}
int search(int st,int ed,int k)
{
    int mid=(st+ed)/2;
    if(k<s2[mid])
        return search(st,mid-1,k);
    else if(k==s2[mid])
        return s1[mid];
    else return search(mid+1,ed,k-s2[mid]);
}
void del(int st,int ed,int k)
{
    int mid=(st+ed)/2;
    if(k<s2[mid] || (k==s2[mid] && s3[mid]<0))
	{
        del(st,mid-1,k);
		s2[mid]--;
	}
    else if(k==s2[mid])
    {
        s3[mid]=-1;
        s2[mid]--;
    }
    else
        del(mid+1,ed,k-s2[mid]);    
}
bool seek(int st,int ed,int num)
{
	if(st>ed)
		return 0;
	int mid=(st+ed)/2;
	if(s2[mid]==num)
		return 1;
	else if(s2[mid]>num)
		return seek(st,mid-1,num);
	else
		return seek(mid+1,ed,num);
}
main()
{
    int i,j,k;
    for(i=0;i<1000000;i++)
        s1[i]=i*2+1;
    n=1000000;
    calc(0,999999);
    for(j=2;j<n;j++)
    {
        k=search(0,999999,j);
        for(i=n/k*k;i>0;i-=k,n--)
            del(0,999999,i);
    }
	for(i=n=0;i<1000000;i++)
		if(s3[i]>=0)s2[n++]=s1[i];
	for(i=0;i<70;i++)
		printf("%d ",s2[i]);
	puts("");
	while(scanf("%d",&i)!=EOF)
	{
		if(i%2)
		{
			puts("n");
			continue;
		}
		for(j=i/2;j>0;j--)
			if(seek(0,n-1,j) && seek(0,n-1,i-j))
			{
				printf("%d %d\n",j,i-j);
				break;
			}
	}
}
