#include<cstdio>
const int N=5005;
char s[N],t[N];
main()
{
    int i,j,k,x,n,mi,mk;
    while(scanf("%d",&n)>0 && n)
    {
        for(j=0;j<n;j++)
            scanf("%s",s+j);
        for(i=mi=1,mk=n;i<=n;i++)
        {
			for(j=k=x=0;j<n;j++)
			{
				if(t[j])x^=1;
				t[j]=0;
				if((s[j]=='B')^x)
				{
                    if(j+i>n)k=n;
				    else t[j+i]=1,x^=1,k++;
				}
			}
			if(k<mk)mk=k,mi=i;
		}
		printf("%d %d\n",mi,mk);
    }
}
