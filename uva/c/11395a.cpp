#include<cstdio>
main()
{
    int i,j,k,n,sum;
    while(scanf("%d",&n)==1)
    {
        sum=0;
        for(i=1;i<=n;i++)
        {
            for(j=1,k=0;j<=i;j++)
            {
                if(i%j)continue;
                k^=j;
            }
            if(k%2)printf("%d\n",i,sum++);
        }
        printf("%d\n",sum);
    }
}