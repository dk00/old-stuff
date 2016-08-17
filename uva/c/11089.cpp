#include<cstdio>
main()
{
    int i,n,t,f[100];
    f[0]=1,f[1]=2;
    for(i=2;i<44;i++)
        f[i]=f[i-1]+f[i-2];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(i=43;f[i]>n;i--);
        for(;i>=0;i--)
        {
            if(n>=f[i])
            {
                putchar('1');
                n-=f[i];
            }
            else putchar('0');
        }
        puts("");
    }
}
