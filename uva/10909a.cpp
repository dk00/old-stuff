#include<cstdio>
#include"bst.h"
Bst s; 
int n,s1[1000001],s2[1000001],s3[1000001];
void calc(int st,int ed)
{
    if(st>ed)return;
    int mid=(st+ed)/2;    
    s.insert(s1[mid]);
    calc(st,mid-1);
    calc(mid+1,ed);
}
main()
{
    int i,j,k;
    for(i=0;i<1000000;i++)
        s1[i]=i*2+1;
    n=1000000;
    calc(0,999999);
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
