#include<cstdio>
main()
{
    int i,j,k,n,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);
        for(i=j=0;i<n;i++)
            (j+=k)%=(1+i);
        printf("Case %d: %d\n",C++,j+1);
    }
}
