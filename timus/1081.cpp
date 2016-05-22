#include<cstdio>
main()
{
    int i,k,n,f[45];
    f[0]=f[1]=1;
    for(i=2;i<=44;i++)
        f[i]=f[i-1]+f[i-2];
    while(scanf("%d %d",&n,&k)==2)
    {
        if(f[n+1]<=--k){puts("-1");continue;}
        for(i=n;i>0;i--)
            if(k>=f[i])
                putchar('1'),k-=f[i];
            else
                putchar('0');
        puts("");
    }
}
