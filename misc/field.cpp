#include<cstdio>
main()
{
    int i,j,n;
    while(scanf("%d",&n) && n)
    {
        printf(" +");
        for(j=0;j<n;j++)
            printf(" %2d",j);
        puts("");
        for(i=0;i<n;i++)
        {
            printf("%2d",i);
            for(j=0;j<n;j++)
                printf(" %2d",(i+j)%n);
            puts("");
        }
        puts("");
        printf(" *");
        for(j=0;j<n;j++)
            printf(" %2d",j);
        puts("");
        for(i=0;i<n;i++)
        {
            printf("%2d",i);
            for(j=0;j<n;j++)
                printf(" %2d",(i*j)%n);
            puts("");
        }
    }
}
