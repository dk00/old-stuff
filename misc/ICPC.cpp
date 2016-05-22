#include<cstdio>
main()
{
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=inf;
        for(i=0;i<n;i++)
        {
            scanf("%d",&j);
            while(j--)
            {
                scanf("%d %d",&k,&l);
                c[i][k-1]=l;
            }
        }
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    c[i][j]<?=(c[i][k]+c[k][j]);
        for(i=0,l=inf;i<n;i++)
        {
            for(j=k=0;j<n;j++)
                k+=c[i][j];
            if(k<min)
                min=k,ans=i;
        }
        if(l<inf)
            printf("%d %d\n",i,min);
        else
            puts("disjoint");
    }
}
