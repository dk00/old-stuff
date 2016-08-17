#include<cstdio>
main()
{
    int i,j,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&i,&j);
        printf("%d\n",(i/3)*(j/3));
    }
}
