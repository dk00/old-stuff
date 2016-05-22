#include<cstdio>
main()
{
    int i,j,k,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        i=100,j=0;
        while(n--)
        {
            scanf("%d",&k);
            i<?=k;
            j>?=k;
        }
        printf("%d\n",(j-i)*2);
    }
}
