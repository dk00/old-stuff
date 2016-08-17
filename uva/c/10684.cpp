#include<cstdio>
main()
{
    int i,j,k,n,max;
    while(scanf("%d",&n) && n)
    {
        max=-1;
        for(i=j=0;i<n;i++)
        {
            scanf("%d",&k);
            j+=k;
            if(j<0)
            {
                j=0;
                continue;
            }
            max>?=j;
        }
        if(max>0)
            printf("The maximum winning streak is %d.\n",max);
        else
            puts("Losing streak.");
    }
}
