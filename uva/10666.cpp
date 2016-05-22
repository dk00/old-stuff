#include<cstdio>
int R(int n)
{
    if(!n)return 0;
    return n%2+R(n/2);
}
int r(int n)
{
    if(n%2)return 0;
    return 1+2*r(n/2);
}
main()
{
    int i,j,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&i,&j);
        printf("%d %d\n",1+R(j),(1<<i)-r(j+(1<<i)));
    }
}
