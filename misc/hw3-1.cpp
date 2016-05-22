#include<stdio.h>
main()
{
    int i,j,k,n,sum=0,s[1000];
    while(scanf("%d",&n)==1)
    {
        for(i=sum=0;i<n;i++)
            scanf("%d",s+i);
        for(i=0;i<n;i++)
            for(j=1;j<n;j++)
                if(s[j]<s[j-1])
                {
                    k=s[j],s[j]=s[j-1],s[j-1]=k;
                    sum++;
                }
        printf("%d\n",sum);
    }
}
