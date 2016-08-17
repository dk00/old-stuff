#include<cstdio>
main()
{
    int i,j,k,l,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        l=k=0,i=-n-1;
        while(n--)
        {
            scanf("%d",&j);
            if(l && i>j)
                l=!l,k++;
            if(!l && i<j)
                l=!l,k++;
            i=j;
        }
        printf("%d\n",k);
    }
}
