#include<cstdio>
const int N=500001;
char s[N];
int p[N];
int test(int l)
{
    int i,j,k;
    for(i=1,j=0;s[i];i++)
    {
	while(j>0 && s[i]!=s[j])j=p[j-1];
	if(s[i]==s[j])j++;
	while(j>l)j=p[j-1];
	p[i]=j;
    }
    for(i=0;s[i];i++)
	printf("%d ",p[i]);
    puts("");
    while(i-->l)
    {
	j--;
	if(p[i]>j)j=p[i];
	if(j<=0)
	{
	    return 0;
	}
    }
    return 1;
}
main()
{
    int i,j,k,l,n;
    while(scanf("%s",s)==1)
    {
	for(n=0;s[n];n++);
	l=n;
	printf("%d\n",test(8));
	for(i=1,j=n-1;i<j;)
	{
	    k=(i+j)/2;
	    if(test(k))l=k,j=k-1;
	    else i=k+1;
	}
	printf("%d\n",l);
    }
}
