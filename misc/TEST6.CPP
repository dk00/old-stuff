#include<cstdio>
main()
{
    int i,j,n,sum;
    char tmp[120];
    while(scanf("%d",&n) && n)
    {
        for(i=sum=0;i<=n;i++)
        {
            sprintf(tmp,"%d",i);
            for(j=0;tmp[j];j++)
                if(tmp[j]=='0')
                    sum++;
        }
        printf("%d\n",sum);
    }
}
