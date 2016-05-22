#include<cstdio>
main()
{
    int i,j,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&i,&j);
        if(i<j)puts("0");
        else printf("%lf\n",1-j/(i+1.0));
    }
}
