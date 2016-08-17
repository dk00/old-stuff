//S(n,k) = S(n,k-1)^n + 1
#include"bigint1.h" // http://phpfi.com/208419
main()
{
    int i,j;
    for(i=1;i<=32;i++)
    {
        s[i][0]=1;
        for(j=1;j<=32 && pow(i,j)<=1024;j++)
            s[i][j]=pow(s[i][j-1],i)+1;
    }
    while(scanf("%d %d",&i,&j)==2 && i+j)
    {
        printf("%d %d ",i,j);
        if(j)
            puts((s[i][j]-s[i][j-1]).tostr());
        else
            puts(s[i][j].tostr());
    }
}
