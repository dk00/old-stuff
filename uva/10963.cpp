#include<cstdio>
main()
{
    int i,j,k,l,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n),n--;
            scanf("%d %d",&j,&k);
        l=j-k,m=1;
        for(i=0;i<n;i++)
        {
            scanf("%d %d",&j,&k);
            if(j-k!=l)m=0;
        }
        if(m)puts("yes");
        else puts("no");
        if(T)puts("");
    }
}
