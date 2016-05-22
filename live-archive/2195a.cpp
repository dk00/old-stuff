#include<cstdio>
main()
{
    int i,j,k,n;
    while(scanf("%d",&n) && n)
    {
        for(i=2,k=0;i<=n;i++)
        {
            j=n;
            while(j%i==0)k++,j/=i;
        }
        printf("%d\n",k);
    }
}
