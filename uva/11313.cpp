#include<cstdio>
main()
{
    int n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        if(m==2)
            printf("%d\n",n-1);
        else if(n%(m-1)==1)
            printf("%d\n",n/(m-1));
        else
            puts("cannot do this");
            
    }
}
