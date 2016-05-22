#include<cstdio>
char find(int n)
{
    unsigned i,j,k;
    for(i=0,j=65535;i<=j;)
    {
        k=(i+j)/2;
        if(k*(k+1)/2<n)i=k+1;
        else if(k*(k+1)/2>n)j=k-1;
        else return 1;
    }
    return 0;
}
main()
{
    int n,C;
    scanf("%d",&C);
    while(C--)
    {
        scanf("%d",&n);
        printf("%d",find(n-1));
        if(C)putchar(' ');
    }
}
