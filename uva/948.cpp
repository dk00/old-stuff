#include<cstdio>
main()
{
    int i,n,T,s[40];
    s[0]=1,s[1]=2;
    for(i=2;i<40;i++)
        s[i]=s[i-1]+s[i-2];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%d = ",n);
        for(i=39;s[i]>n;i--);
        for(;i>=0;i--)
        {
            if(n>=s[i])
            {
                n-=s[i];
                putchar('1');
            }
            else putchar('0');
        }
        puts(" (fib)");
    }
}
